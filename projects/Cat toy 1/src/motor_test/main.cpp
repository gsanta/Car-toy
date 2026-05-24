#include <Arduino.h>

// Motor 1 pins (X axis)
const uint8_t MOTOR_X_STEP_PIN = 4;
const uint8_t MOTOR_X_DIR_PIN = 5;

// Motor 2 pins (Y axis)
const uint8_t MOTOR_Y_STEP_PIN = 3;
const uint8_t MOTOR_Y_DIR_PIN = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("SIMPLE MOTOR TEST - Direct pin toggle");
  
  // Set motor pins as outputs
  pinMode(MOTOR_X_STEP_PIN, OUTPUT);
  pinMode(MOTOR_X_DIR_PIN, OUTPUT);
  pinMode(MOTOR_Y_STEP_PIN, OUTPUT);
  pinMode(MOTOR_Y_DIR_PIN, OUTPUT);
  
  // Set direction pins to HIGH (one direction)
  digitalWrite(MOTOR_X_DIR_PIN, HIGH);
  digitalWrite(MOTOR_Y_DIR_PIN, HIGH);
  
  // Set step pins LOW initially
  digitalWrite(MOTOR_X_STEP_PIN, LOW);
  digitalWrite(MOTOR_Y_STEP_PIN, LOW);
  
  Serial.println("Setup complete - motors should spin now");
}

void loop() {
  // Toggle X motor STEP pin every 3ms (pulse width 1.5ms on/off)
  digitalWrite(MOTOR_X_STEP_PIN, HIGH);
  delayMicroseconds(1500);
  digitalWrite(MOTOR_X_STEP_PIN, LOW);
  delayMicroseconds(1500);
  
  // Toggle Y motor STEP pin every 3ms
  digitalWrite(MOTOR_Y_STEP_PIN, HIGH);
  delayMicroseconds(1500);
  digitalWrite(MOTOR_Y_STEP_PIN, LOW);
  delayMicroseconds(1500);
}
