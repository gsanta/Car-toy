#include "limit_switch.h"

LimitSwitch::LimitSwitch(int pin) : pin(pin), triggered(false) {}

void LimitSwitch::setup() {
  pinMode(pin, INPUT_PULLUP);
}

void LimitSwitch::checkTriggered() {
  triggered = digitalRead(pin) == LOW;
}

bool LimitSwitch::isTriggered() {
  return triggered;
}

void LimitSwitch::reset() {
  triggered = false;
}
