#include "motor_driver_a4988.h"

MotorDriverA4988::MotorDriverA4988(uint8_t stepPin, uint8_t dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

bool MotorDriverA4988::isRunning() {
  return is_running;
}

void MotorDriverA4988::setDirection(uint8_t direction) {
  if (direction == UP) {
    digitalWrite(dirPin, HIGH);
  } else if (direction == DOWN) {
    digitalWrite(dirPin, LOW);
  }
}

void MotorDriverA4988::rotate() {
  is_running = true;
  digitalWrite(stepPin, HIGH);
}


void MotorDriverA4988::stop() {
    is_running = false;
    digitalWrite(stepPin, LOW);
}