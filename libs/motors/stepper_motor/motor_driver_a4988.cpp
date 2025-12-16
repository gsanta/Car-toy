#include "motor_driver_a4988.h"

MotorDriverA4988::MotorDriverA4988(uint8_t stepPin, uint8_t dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void MotorDriverA4988::setDirection(uint8_t direction) {
  if (direction == UP) {
    digitalWrite(dirPin, HIGH);
  } else if (direction == DOWN) {
    digitalWrite(dirPin, LOW);
  }
}

void MotorDriverA4988::rotate() {
  digitalWrite(stepPin, HIGH);
}


void MotorDriverA4988::stop() {
    digitalWrite(stepPin, LOW);
}