#include <Adafruit_PWMServoDriver.h>
#include "stewart_platform_v2.h"
#include "stewart_platform_v2_initialize.h"
#include "stewart_platform_v2_terminate.h"
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40); 

// Standard analog servo pulse width boundaries (at 50Hz updates)
// These values represent the internal 12-bit PCA9685 counter steps (0-4095)
#define SERVOMIN  109 // Minimum pulse length count for 0 degrees (~500 µs)
#define SERVOMAX  479 // Maximum pulse length count for 180 degrees (~2500 µs)   

// Define the channel on the PCA9685 where the servo is plugged in
//const int servoChannel = 0; 

double initial_angle[] = {0,0,0,0,0,0};
double final_angle[]={90,90,90,90,90,90};
double current_angle[]={0,0,0,0,0,0};
double max_velocity = 60.0; // Maximum servo speed (degrees per second)
double dt = 0.02; // Step time interval (seconds) for your control loop 50Hz
double max_fabs_dq = 0;
double min_fabs_dq = 0;
double T_max;
int num_steps;
int counter = 0;
bool target_reached = false;
const int interruptPin = 7;

const int pin_dy = 5; // Y-axis
const int pin_dz = 4; // Z-axis
const int pin_Roll = 15; // Roll potentiometer
const int pin_Pitch = 16; // Pitch potentiometer
const int pin_Yaw = 17; // Yaw potentiometer
const int pin_dx = 18; // General potentiometer for testing
int lastX, lastY, lastZ, lastRoll, lastPitch, lastYaw;
const int THRESHOLD = 20;   // Ignore small ADC noise


// MUST use 'volatile' so the compiler knows this changes inside an ISR
volatile bool actionTriggered = false; 

double yaw = 0, pitch = 0, roll = 0, dx = 0, dy = 0, dz = 0;

void setup() {
  // put your setup code here, to run once:
  stewart_platform_v2_initialize();
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
  lastX = analogRead(pin_dx);
  lastY = analogRead(pin_dy);
  lastZ = analogRead(pin_dz);
  lastRoll = analogRead(pin_Roll);
  lastPitch = analogRead(pin_Pitch);
  lastYaw = analogRead(pin_Yaw);
}


void loop() { 

  int joy_dy = analogRead(pin_dy);
  int joy_dz = analogRead(pin_dz);
  int joy_dx = analogRead(pin_dx);
  int joy_roll = analogRead(pin_Roll);
  int joy_pitch = analogRead(pin_Pitch); 
  int joy_yaw = analogRead(pin_Yaw);
  
  if(joystickMoved()){
    Serial.println("Joystick moved OUTSIDE the movement bounds, interrupting current movement.");
    actionTriggered = true; 
    return; // Exit the loop to handle the new action
  }

  if (actionTriggered) {
    //calculate final angle for each servo based on the desired end-effector position
    Serial.println("Action triggered, calculating new target angles.");
    //calculating final angles of servo
    yaw = map(joy_yaw, 0, 4095, -15, 15);
    pitch = map(joy_pitch, 0, 4095, -15, 15);
    roll = map(joy_roll, 0, 4095, -15, 15);
    dx = map(joy_dx, 0, 4095, -15, 15);
    //dx = 0; // Assuming dx is not used in this context
    dy = map(joy_dy, 0, 4095, -15, 15);
    dz = map(joy_dz, 0, 4095, -15, 15);
    stewart_platform_v2(yaw,pitch,roll,dx,dy,dz,final_angle);
    for(int i=0;i<6;i++){      
      final_angle[i] += 90; // Adjusting for servo's 0-180 degree range
      Serial.print("Final angle for servo "); Serial.print(i); Serial.print(": "); Serial.println(final_angle[i]);
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
    Serial.println("already at destination!");
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
    }

    // Command physical servos
    run_servo(current_angle);

    //for the next loop put initial angle as the current angle
    for (int i = 0; i < 6; i++) {
      initial_angle[i] = current_angle[i];
    }

    if(joystickMoved()){
      Serial.println("Joystick moved INSIDE the movement bounds, interrupting current movement.");
      actionTriggered = true; 
      return; // Exit the loop to handle the new action
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
  target_reached = true;
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

bool joystickMoved() {
  int joy_dy_ = analogRead(pin_dy);
  int joy_dz_ = analogRead(pin_dz);
  int joy_dx_ = analogRead(pin_dx);
  int joy_roll_ = analogRead(pin_Roll);
  int joy_pitch_ = analogRead(pin_Pitch); 
  int joy_yaw_ = analogRead(pin_Yaw);


  if (abs(joy_dx_ - lastX) > THRESHOLD || abs(joy_dy_ - lastY) > THRESHOLD || abs(joy_dz_ - lastZ) > THRESHOLD || abs(joy_roll_ - lastRoll) > THRESHOLD || abs(joy_pitch_ - lastPitch) > THRESHOLD || abs(joy_yaw_ - lastYaw) > THRESHOLD) {
    lastX = joy_dx_;
    lastY = joy_dy_;
    lastZ = joy_dz_;
    lastRoll = joy_roll_;
    lastPitch = joy_pitch_;
    lastYaw = joy_yaw_;
    return true;
  }
  return false;
}