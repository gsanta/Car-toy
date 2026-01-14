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
    Serial.print("X Stage: ");
    Serial.print(xVal);
    Serial.print(" Y Stage: ");
    Serial.println(yVal);

    if (xVal > 0) {
      joystickController->getBeltDriver().moveRight();
    } else if (xVal < 0) {
      joystickController->getBeltDriver().moveLeft();
    } else {
      joystickController->getBeltDriver().stopMotor();
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
