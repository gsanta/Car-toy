#include "motor_driver_a4988.h"

namespace {
constexpr int MAX_SPEED_MODE = 3;
constexpr int BASE_DELAY_US = 3600;
constexpr int MIN_DELAY_US = 1200;
constexpr int RAMP_STEP_US = 80;
}

MotorDriverA4988::MotorDriverA4988(uint8_t stepPin, uint8_t dirPin) : stepPin(stepPin), dirPin(dirPin) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void MotorDriverA4988::setDirection(uint8_t direction) {
  const bool directionChanged = this->direction != direction;

  if (direction == UP) {
    digitalWrite(dirPin, HIGH);
    this->direction = UP;
  } else if (direction == DOWN) {
    digitalWrite(dirPin, LOW);
    this->direction = DOWN;
  }

  // Re-ramp after reversing to avoid instant high-speed direction changes.
  if (directionChanged) {
    currentDelayUs = BASE_DELAY_US;
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
  this->speed = constrain(speed, 1, MAX_SPEED_MODE);
}

int MotorDriverA4988::getSpeed() {
    return speed;
}

int MotorDriverA4988::getDelay() {
  // Higher speed mode means lower target delay between STEP pulses.
  int targetDelayUs = BASE_DELAY_US / speed;
  if (targetDelayUs < MIN_DELAY_US) {
    targetDelayUs = MIN_DELAY_US;
  }

  // Gradually move toward target delay to provide a basic acceleration ramp.
  if (currentDelayUs > targetDelayUs) {
    currentDelayUs -= RAMP_STEP_US;
    if (currentDelayUs < targetDelayUs) {
      currentDelayUs = targetDelayUs;
    }
  } else if (currentDelayUs < targetDelayUs) {
    currentDelayUs += RAMP_STEP_US;
    if (currentDelayUs > targetDelayUs) {
      currentDelayUs = targetDelayUs;
    }
  }

  return currentDelayUs;
}

bool MotorDriverA4988::isRunning() {
  return is_running;
}

void MotorDriverA4988::setIsRunning(bool running) {
    is_running = running;
    if (!running) {
      currentDelayUs = BASE_DELAY_US;
    }
}

void MotorDriverA4988::pulse() {
    if (!is_running) {
        return;  // Don't pulse if the motor isn't running
    }

    // Create a complete STEP pulse on each timer tick.
    high();
    delayMicroseconds(5);
    low();
}