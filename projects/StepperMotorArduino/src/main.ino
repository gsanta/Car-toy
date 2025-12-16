#include <Arduino.h>
#include "../lib/motors/stepper_motor/motor_driver_a4988.h"

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3

// Create motor instance
MotorDriverA4988 motor(STEP_PIN, DIR_PIN);

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Motor is initialized by constructor
  Serial.println("Motor initialized");
}

void loop() {
  // Add your main code here, to run repeatedly
}
