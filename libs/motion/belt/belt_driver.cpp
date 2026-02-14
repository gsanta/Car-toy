#include "belt_driver.h"

BeltDriver::BeltDriver(int leftPin, int rightPin, TimerControl& timerControl, StepperMotorDriver& stepperMotor)
  : TimerHandler(100), beltLimiter(leftPin, rightPin), timerControl(timerControl), stepperMotor(stepperMotor), beltDriverTimer(*this) {
    beltLimiter.setup();
    timerControl.add_millisecond_handler(this);
    timerControl.add_microsecond_handler(&beltDriverTimer);
}

BeltDriver::~BeltDriver() {
}

void BeltDriver::pulse() {
  stepperMotor.pulse();
}

bool BeltDriver::isMovementBlocked() {
  if (beltLimiter.getLeftLimit().isTriggered() && stepperMotor.getDirection() == DOWN) {
    return true;
  } else if (beltLimiter.getRightLimit().isTriggered() && stepperMotor.getDirection() == UP) {
    return true;
  }
  return false;
}

StepperMotorDriver& BeltDriver::getStepperMotor() {
  return stepperMotor;
}

void BeltDriver::handleTimerEvent() {
  beltLimiter.checkLimits();
}