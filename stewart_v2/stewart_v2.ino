#include "stewart_platform_v2.h"
#include "stewart_platform_v2_initialize.h"
#include "stewart_platform_v2_terminate.h"
double initial_angle[] = {0,0,0,0,0,0};
double final_angle[]={0,0,0,0,0,0};
double current_angle[]={0,0,0,0,0,0};
double max_velocity = 10.0; // Maximum servo speed (degrees per second)
double dt = 0.02; // Step time interval (seconds) for your control loop 50Hz
double max_fabs_dq = 0;
double T_max;
int num_steps;
int counter = 0;
bool target_reached = false;

void setup() {
  // put your setup code here, to run once:
  stewart_platform_v2_initialize();
  Serial.begin(9600);
}

void loop() {
  //do not proceed further if target has reached
  if(target_reached)
    return;

  //calculating final angles of servo
  stewart_platform_v2(10,-2,1,20,2,6,final_angle);

  //check for nan value
  if(isnan(final_angle[0])){
    target_reached = true;
    Serial.print("Can't proceed further");
    return;
  }

  double dq_abs[6];
  for(int i=0;i<6;i++){
    dq_abs[i] = fabs(final_angle[i]-initial_angle[i]);
  }
  max_fabs_dq = 0;
  for(int i=0;i<6;i++){
    if(dq_abs[i]>max_fabs_dq){
      max_fabs_dq = dq_abs[i];
    }
  }
  Serial.println(max_fabs_dq);
  // ADDED: Check if platform is already at destination
  if (max_fabs_dq < 1e-4) {
    target_reached = true;
    return;
  }

  T_max = 1.875*max_fabs_dq/max_velocity;
  num_steps = ceil(T_max/dt);
  if(num_steps < 2){
    num_steps = 2;
  }

  //for calculating the coefficients of the polynomial equation
  double a[6];
  double b[6];
  double c[6];
  double f[6];
  double nf = num_steps-1;
  for(int servo_number=0;servo_number<6;servo_number++){
      a[servo_number] = -6*(initial_angle[servo_number]-final_angle[servo_number])/pow(nf,5);
      b[servo_number] = 15*(initial_angle[servo_number]-final_angle[servo_number])/pow(nf,4);
      c[servo_number] = -10*(initial_angle[servo_number]-final_angle[servo_number])/pow(nf,3);
      f[servo_number] = initial_angle[servo_number];
  }

  //calculation of angle for all six servos at each step
  for(int steps=0;steps<num_steps;steps++){
    unsigned long start_time = millis();
    for(int servo_number=0;servo_number<6;servo_number++){
      double theta = a[servo_number]*pow(steps,5) + b[servo_number]*pow(steps,4) + c[servo_number]*pow(steps,3) + f[servo_number];
      current_angle[servo_number] = theta;
      Serial.print(theta); Serial.print(" ");
    }
    Serial.println("");

    // Command physical servos
    run_servo(current_angle);

    // Maintain strict 50Hz (20ms) timing
    while (millis() - start_time < (dt * 1000)) {
      // Wait for remainder of step duration
    }
  }

  //for the next loop put initial angle as the current angle
  for (int i = 0; i < 6; i++) {
    initial_angle[i] = current_angle[i];
  }

  Serial.println("=======Final Angle=======");
  for (int i = 0; i < 6; i++) {
    Serial.print(final_angle[i]);
    Serial.print(" ");
  }
  Serial.println("");
}


void run_servo(double input_angles[]){
  //commands for servo goes here
}
