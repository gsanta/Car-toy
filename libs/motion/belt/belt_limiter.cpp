#include "belt_limiter.h"

BeltLimiter::BeltLimiter(int leftPin, int rightPin)
  : leftLimit(leftPin), rightLimit(rightPin) {}

void BeltLimiter::setup() {
  leftLimit.setup();
  rightLimit.setup();
}

void BeltLimiter::checkLimits() {
  leftLimit.checkTriggered();
  rightLimit.checkTriggered();
}

LimitSwitch& BeltLimiter::getLeftLimit() {
  return leftLimit;
}

LimitSwitch& BeltLimiter::getRightLimit() {
  return rightLimit;
}
