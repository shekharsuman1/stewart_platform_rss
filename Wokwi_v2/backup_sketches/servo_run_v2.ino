#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40); 

// Standard analog servo pulse width boundaries (at 50Hz updates)
// These values represent the internal 12-bit PCA9685 counter steps (0-4095)
#define SERVOMIN  109 // Minimum pulse length count for 0 degrees (~500 µs)
#define SERVOMAX  479 // Maximum pulse length count for 180 degrees (~2500 µs)   

// Define the channel on the PCA9685 where the servo is plugged in
//const int servoChannel = 0; 

double initial_angle[] = {0,0,0,0,0,0};
double final_angle[]={0,0,0,0,0,0};
double current_angle[]={0,0,0,0,0,0};
double max_velocity = 120.0; // Maximum servo speed (degrees per second)
double dt = 0.02; // Step time interval (seconds) for your control loop 50Hz
double max_fabs_dq = 0;
double min_fabs_dq = 0;
double T_max;
int num_steps;
int counter = 0;
bool target_reached = false;
const int interruptPin = 5;

// MUST use 'volatile' so the compiler knows this changes inside an ISR
volatile bool actionTriggered = false; 

void setup() {
  // put your setup code here, to run once:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), myISR, RISING);
  Serial.begin(115200);
  Serial.println("16 channel Servo test!");
  board1.begin();
  board1.setOscillatorFrequency(27000000); // Set internal oscillator frequency
  board1.setPWMFreq(50); 
  delay(10);
  for(int i=0;i<6;i++){
    setServoAngle(i, 90); // Set initial position to 90 degrees
  }
  delay(1000); // Allow time for servos to reach the initial position
}

void loop() {
  // 1. Check the built-in background interrupt buffer
  

  // 2. Immediate conditional action execution
  if (actionTriggered) {
    //calculate final angle for each servo based on the desired end-effector position
    Serial.println("Action triggered, calculating new target angles.");
    for(int i=0;i<6;i++){
      long random_angle = random(-90, 90); // Generate a random angle between -90 and 90 degrees
      final_angle[i] = random_angle + 90; // Adjusting for servo's 0-180 degree range
    }    
    target_reached = false; // Reset target reached flag for new movement
    actionTriggered = false; // Reset the flag
  }


  //do not proceed further if target has reached
  if(target_reached){
    //Serial.println("Target reached, no further movement required.");
    return;
  }

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

  min_fabs_dq = INFINITY;
  for(int i=0;i<6;i++){
    if(dq_abs[i]<min_fabs_dq){
      min_fabs_dq = dq_abs[i];
    }
  }

  // ADDED: Check if platform is already at destination
  if (min_fabs_dq < 1e-4) {
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
      //Serial.print(theta); Serial.print(" ");
    }
    //Serial.println("");

    // Command physical servos
    run_servo(current_angle);

    //for the next loop put initial angle as the current angle
    for (int i = 0; i < 6; i++) {
      initial_angle[i] = current_angle[i];
    }

    if(actionTriggered){
      Serial.println("New action triggered, interrupting current movement.");
      //actionTriggered = false; // Reset the flag for the next action
      // If a new action is triggered, 
      return; // Exit the loop to handle the new action
    }

    // Maintain strict 50Hz (20ms) timing
    while (millis() - start_time < (dt * 1000)) {
      // Wait for remainder of step duration
    }
  } 
  delay(1000); // Optional: wait for a second before next movement
}

void run_servo(double angles[]){
  for(int servoChannel=0;servoChannel<6;servoChannel++){
    setServoAngle(servoChannel, angles[servoChannel]);
  }
}


// Custom helper function to map degree angles directly into PCA9685 pulse counts
void setServoAngle(int channel, int angle) {
  // Constrain the input angle to safe boundaries
  angle = constrain(angle, 0, 180);
  
  // Map 0-180 degrees into the required SERVOMIN to SERVOMAX range
  int pulseLength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  
  // Write the pulse duration to the driver channel
  board1.setPWM(channel, 0, pulseLength);
}

void myISR() {
  // This triggers instantly, even mid-loop, and changes the flag
  actionTriggered = true; 
}