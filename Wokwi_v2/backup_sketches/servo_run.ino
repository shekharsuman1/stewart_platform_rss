#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40); 

// Standard analog servo pulse width boundaries (at 50Hz updates)
// These values represent the internal 12-bit PCA9685 counter steps (0-4095)
#define SERVOMIN  110 // Minimum pulse length count for 0 degrees (~500 µs)
#define SERVOMAX  600 // Maximum pulse length count for 180 degrees (~2500 µs)   

// Define the channel on the PCA9685 where the servo is plugged in
//const int servoChannel = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("16 channel Servo test!");
  board1.begin();
  board1.setOscillatorFrequency(27000000); // Set internal oscillator frequency
  board1.setPWMFreq(50); 
  delay(10);
}

void loop() {
  runServo();
}

void runServo(){
  // Sweep from 0 to 180 degrees
  //Serial.println("Sweeping from 0 to 180...");
  for (int angle = 0; angle <= 90; angle += 5) {
    for(int servoChannel=0;servoChannel<6;servoChannel++){
      setServoAngle(servoChannel, angle);
    }
    delay(30); 
  }
  
  delay(0); // Hold at 180 degrees for 1 second

  // Sweep back from 180 to 0 degrees
  //Serial.println("Sweeping from 180 to 0...");
  for (int angle = 90; angle >= 0; angle -= 5) {
    for(int servoChannel=0;servoChannel<6;servoChannel++){
      setServoAngle(servoChannel, angle);
    }
    delay(30);
  }

  delay(0); // Hold at 0 degrees for 1 second
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

