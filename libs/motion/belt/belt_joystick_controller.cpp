#include "belt_joystick_controller.h"
#include "belt_driver.h"

BeltJoystickController::BeltJoystickController(BeltDriver& beltDriver, Joystick& joystick) 
  : StagedJoystickReader(maxSpeed, joystick), beltDriver(beltDriver) {
}

BeltJoystickController::~BeltJoystickController() {
}

BeltDriver& BeltJoystickController::getBeltDriver() {
  return beltDriver;
}

void BeltJoystickController::handleStagedMove(int xVal, int yVal) {
    // Set speed based on yVal (0 = don't set, 1 or 2 = set speed)
  if (xVal == 0) {
    beltDriver.getStepperMotor().stop();
  } else {
    int speed = maxSpeed - abs(xVal) + 1;

    if (xVal > 0) {
      beltDriver.moveRight();
    } else if (xVal < 0) {
      beltDriver.moveLeft();
    }

    beltDriver.getStepperMotor().setSpeed(abs(yVal));
    beltDriver.getStepperMotor().rotate();
  }
}

void BeltJoystickController::handleClick(int buttonState) {
  if (joystickController != nullptr && buttonState == 1) {
    if (joystickController->getBeltDriver().getIsRunning()) {
      joystickController->getBeltDriver().stopMotor();
      Serial.println("Stepper stopped");
    } else {
      joystickController->getBeltDriver().startMotor();
      Serial.println("Stepper started");
    }
  }
}
