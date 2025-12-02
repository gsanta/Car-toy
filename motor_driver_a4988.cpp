#include "motor_driver_a4988.h"

MotorDriverA4988::MotorDriverA4988(uint8_t stepPin, uint8_t dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // digitalWrite(dirPin, LOW);
}

void MotorDriverA4988::setDirection(uint8_t direction) {
  if (direction == UP) {
    digitalWrite(dirPin, HIGH);
  } else if (direction == DOWN) {
    digitalWrite(dirPin, LOW);
  }
}

void MotorDriverA4988::stop() {
  stopped = true;
}

void MotorDriverA4988::start() {
  stopped = false;
}

bool MotorDriverA4988::isStopped() {
  return stopped;
}

void MotorDriverA4988::handleTimerEvent() {
  if (stopped) {
    return;
  }

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(2); // Short pulse, adjust as needed (2-10us typical)
  digitalWrite(stepPin, LOW);


  // if (lastStepVoltage == LOW) {  
  //   digitalWrite(stepPin, HIGH);
  //   lastStepVoltage = HIGH;
  // } else {
  //   digitalWrite(stepPin, LOW);
  //   lastStepVoltage = LOW;
  // }
}
