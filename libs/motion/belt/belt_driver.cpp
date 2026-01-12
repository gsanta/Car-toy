#include "belt_driver.h"

BeltDriver::BeltDriver(int leftPin, int rightPin, TimerControl& timerControl, StepperMotorDriver& stepperMotor)
  : beltLimiter(leftPin, rightPin), limiterAdapter(beltLimiter, *this), timerControl(timerControl), stepperMotor(stepperMotor), stepperAdapter(stepperMotor), isRunning(false) {
    beltLimiter.setup();
    timerControl.add_millisecond_handler(&limiterAdapter);
}

BeltDriver::~BeltDriver() {
}

void BeltDriver::moveLeft() {
  if (beltLimiter.getLeftLimit().isTriggered()) {
    return;
  }

  if (!isRunning) {
    startMotor();
  }

  stepperMotor.setDirection(DOWN);
}

void BeltDriver::moveRight() {
  if (beltLimiter.getRightLimit().isTriggered()) {
    return;
  }

  if (!isRunning) {
    startMotor();
  }

  stepperMotor.setDirection(UP);
}

void BeltDriver::startMotor() {
  if (!isRunning) {
    timerControl.add_microsecond_handler(&stepperAdapter);
    isRunning = true;
  }
}

void BeltDriver::stopMotor() {
  if (isRunning) {
    timerControl.remove_microsecond_handler(&stepperAdapter);
    isRunning = false;
  }
}

bool BeltDriver::getIsRunning() const {
  return isRunning;
}
