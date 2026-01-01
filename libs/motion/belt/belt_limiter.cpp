#include "belt_limiter.h"
#include "limit_reached_command.h"

BeltLimiter::BeltLimiter(int leftPin, int rightPin)
  : leftLimit(leftPin), rightLimit(rightPin) {}

void BeltLimiter::setup() {
  leftLimit.setup();
  rightLimit.setup();
}

void BeltLimiter::checkLimits(LimitReachedCommand& command) {
  leftLimit.checkTriggered();
  rightLimit.checkTriggered();

  if (leftLimit.isTriggered()) {
    Serial.println("Left limit reached");
    command.execute(LimitSide::LEFT_SIDE);
  }

  if (rightLimit.isTriggered()) {
    Serial.println("Right limit reached");
    command.execute(LimitSide::RIGHT_SIDE);
  }
}

LimitSwitch& BeltLimiter::getLeftLimit() {
  return leftLimit;
}

LimitSwitch& BeltLimiter::getRightLimit() {
  return rightLimit;
}
