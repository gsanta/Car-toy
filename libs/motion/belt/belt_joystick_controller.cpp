#include "belt_joystick_controller.h"
#include "belt_driver.h"

BeltJoystickController::BeltJoystickController(BeltDriver& beltDriver, StagedJoystickManager& joystickManager) 
  : beltDriver(beltDriver), joystickManager(joystickManager), commandHandler() {
  commandHandler.setController(this);
  joystickManager.addCommandHandler(&commandHandler);
}

BeltJoystickController::~BeltJoystickController() {
}

BeltDriver& BeltJoystickController::getBeltDriver() {
  return beltDriver;
}

void BeltJoystickControllerCommandHandler::handleMove(int xVal, int yVal) {
  if (joystickController != nullptr) {
    // Set speed based on yVal (0 = don't set, 1 or 2 = set speed)
    if (yVal != 0) {
      joystickController->getBeltDriver().getStepperMotor().setSpeed(yVal);
    }

    if (xVal > 0) {
      joystickController->getBeltDriver().moveRight();
      Serial.println("Moving right");
    } else if (xVal < 0) {
      joystickController->getBeltDriver().moveLeft();
      Serial.println("Moving left");
    } else {
      // joystickController->getBeltDriver().stopMotor();
      // Serial.println("Motor stopped");
    }
  }
}

void BeltJoystickControllerCommandHandler::handleClick(int buttonState) {
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
