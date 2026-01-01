#include "belt_driver.h"

BeltDriver::BeltDriver(BeltLimiter& beltLimiter, LimitReachedCommand& command, TimerControl& timerControl, StepperMotorDriver* stepperMotor)
  : beltLimiter(beltLimiter), command(command), timerControl(timerControl), stepperMotor(stepperMotor), isRunning(false) {
  stepperAdapter = new StepperMotorTimerAdapter(stepperMotor);
}

BeltDriver::~BeltDriver() {
  delete stepperAdapter;
}

void BeltDriver::moveLeft() {
  if (beltLimiter.getLeftLimit().isTriggered()) {
    return;
  }
  stepperMotor->setDirection(DOWN);
}

void BeltDriver::moveRight() {
  if (beltLimiter.getRightLimit().isTriggered()) {
    return;
  }
  stepperMotor->setDirection(UP);
}

void BeltDriver::handleTimerEvent() {
  beltLimiter.checkLimits(command);
}
