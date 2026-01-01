#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <Arduino.h>

class LimitSwitch {
private:
  int pin;
  bool triggered;

public:
  LimitSwitch(int pin);
  void setup();
  void checkTriggered();
  bool isTriggered();
  void reset();
};

#endif
