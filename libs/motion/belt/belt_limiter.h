#ifndef BELT_LIMITER_H
#define BELT_LIMITER_H

#include "../../logic/limit_switch/limit_switch.h"

enum LimitSide {
  LEFT_SIDE,
  RIGHT_SIDE
};

class BeltLimiter {
private:
  LimitSwitch leftLimit;
  LimitSwitch rightLimit;

public:
  BeltLimiter(int leftPin, int rightPin);
  void setup();
  void checkLimits();
  
  LimitSwitch& getLeftLimit();
  LimitSwitch& getRightLimit();
};

#endif
