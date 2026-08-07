function final_angle = stewart_platform_v2(yaw, pitch, roll, dx, dy, dz)
%#codegen
% This directive forces MATLAB to check for C-compatibility in real-time.

%% Preallocation & Structural Layout
theta_NR = NaN(1, 6);

% Platform coordinates in the platform frame
platform = [ 43.20, -35.18, -2.5; 
    -43.20, -35.18, -2.5; 
    -52.07, -19.82, -2.5; 
    -8.87,  55.00, -2.5; 
    8.87,  55.00, -2.5; 
    52.07, -19.82, -2.5];

%% 1. Platform Orientation & Translation
rotation_matrix = rotz(yaw) * roty(pitch) * rotx(roll);

% Apply rotation and translate platform to the base frame
rotatedPlatform = (rotation_matrix * platform')';

% Base offset distance in z-direction (240.33) added to your input dz
total_dz = 240.33 + dz; 

translatedPlatform = rotatedPlatform + [dx, dy, total_dz];

%% 2. Homogeneous Transformation Matrices (HTMs: Servo to Base)
H_1 = [-1.0,  0.0,  0.0,   42.7350;  0.0,  0.0,  1.0, -115.0000;  0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];
H_2 = [ 1.0,  0.0,  0.0,  -42.7350;  0.0,  0.0, -1.0, -115.0000;  0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];
H_3 = [ 0.5, -0.0,  0.866, -120.9604; 0.866, 0.0, -0.5,   20.4904;  0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];
H_4 = [-0.5,  0.0, -0.866,  -78.2254;-0.866, 0.0,  0.5,   94.5096;  0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];
H_5 = [ 0.5,  0.0, -0.866,   78.2254;-0.866, 0.0, -0.5,   94.5096;  0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];
H_6 = [-0.5, -0.0,  0.866,  120.9604; 0.866, 0.0,  0.5,   20.4904; -0.0,  1.0,  0.0,   10.0000;  0.0,  0.0,  0.0,  1.0];

rotation_matrices = cat(3, H_1, H_2, H_3, H_4, H_5, H_6);
solution_new = 0;

%% 3. Kinematic Solver Loop (Newton-Raphson)
tolerance = 0.0001; 
max_iterations = 20;
L = 244; % Link length
R = 35;  % Servo arm length

for i = 1:6
    solution_initial = 0.0;
    counter = 1;
    err = 1.0; 

    q_x = translatedPlatform(i,1);
    q_y = translatedPlatform(i,2);
    q_z = translatedPlatform(i,3);

    HTM = rotation_matrices(:,:,i);
    a = HTM(1,1); c = HTM(1,3); d = HTM(1,4);
    e = HTM(2,1); g = HTM(2,3); h = HTM(2,4);
    j = HTM(3,2); l = HTM(3,4);

    u = d - q_x;
    v = h - q_y;
    w = l - q_z;

    A = R^2 * (a^2 + e^2 - j^2);
    B = 2.0 * R * (u*a + v*e);
    C = 2.0 * R * w * j;
    D = u^2 + v^2 + w^2 + (j^2 * R^2) - L^2;

    while err > tolerance && counter <= max_iterations
        fx  = f(solution_initial, A, B, C, D);
        dfx = df(solution_initial, A, B, C, D);

        % Safeguard against zero derivative
        if abs(dfx) < 1e-12
            counter = 21; 
            break;
        end

        solution_new = solution_initial - (fx / dfx);
        err          = abs(solution_new - solution_initial);

        solution_initial = solution_new;
        counter          = counter + 1;
    end

    if err <= tolerance && counter <= max_iterations
        theta_NR(i) = 2.0 * atand(solution_new);  % Output in degrees
    else
        break;
    end
end

final_angle = theta_NR;
if ~any(isnan(final_angle))
    final_angle = theta_NR;
else
    final_angle = NaN(1,6);
end

%% Local Functions (C-Compatible)
    function fx = f(t, A, B, C, D)
        fx = (A-B+D)*t^4 + 2.0*C*t^3 + (-2.0*A+2.0*D)*t^2 + 2.0*C*t + A+B+D;
    end

    function dfx = df(t, A, B, C, D)
        dfx = 4.0*(A-B+D)*t^3 + 6.0*C*t^2 + 4.0*(-A+D)*t + 2.0*C;
    end

end