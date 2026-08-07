#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Initialise the driver using the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_CHANNEL 0 // The channel your servo is plugged into

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Pulse Calibration Test");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at 50Hz

  Serial.println("Enter a tick value between 100 and 520 in the Serial Monitor.");
}

void loop() {
  if (Serial.available() > 0) {
    int ticks = Serial.parseInt();
    
    // Discard any newline or carriage return characters
    while(Serial.available() > 0) { Serial.read(); }

    if (ticks >= 100 && ticks <= 550) {
      Serial.print("Sending raw tick value: ");
      Serial.println(ticks);
      
      // Send raw tick count to the PCA9685 channel
      pwm.setPWM(SERVO_CHANNEL, 0, ticks);
    } else if (ticks != 0) {
      Serial.println("Invalid input! Please enter a value between 100 and 550.");
    }
  }
}
