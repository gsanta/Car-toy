#include "motor_driver_a4988.h"

MotorDriverA4988::MotorDriverA4988(uint8_t stepPin, uint8_t dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void MotorDriverA4988::setDirection(uint8_t direction) {
  if (direction == UP) {
    digitalWrite(dirPin, HIGH);
    this->direction = UP;
  } else if (direction == DOWN) {
    digitalWrite(dirPin, LOW);
    this->direction = DOWN;
  }
}

uint8_t MotorDriverA4988::getDirection() {
    return direction;
}

void MotorDriverA4988::high() {
  digitalWrite(stepPin, HIGH);
}


void MotorDriverA4988::low() {
  digitalWrite(stepPin, LOW);
}

void MotorDriverA4988::setSpeed(int speed) {
    this->speed = speed;
}

int MotorDriverA4988::getSpeed() {
    return speed;
}

int MotorDriverA4988::getDelay() {
    // Higher speed = smaller delay
    // Speed 1 = 1000ms, Speed 2 = 500ms, Speed 3 = 333ms, etc.
    if (speed <= 0) {
        return 1000;
    }
    return 1000 / speed;
}

bool MotorDriverA4988::isRunning() {
  return is_running;
}

void MotorDriverA4988::setIsRunning(bool running) {
    is_running = running;
}

void MotorDriverA4988::pulse() {
    if (!is_running) {
        return;  // Don't pulse if the motor isn't running
    }

    static bool pulseState = false;
    
    if (!pulseState) {
      high();
      pulseState = true;
    } else {
      low();
      pulseState = false;
    }
}