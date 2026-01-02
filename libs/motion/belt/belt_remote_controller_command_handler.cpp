#include "belt_remote_controller_command_handler.h"
#include "belt_remote_controller.h"
#include "belt_driver.h"

BeltRemoteControllerCommandHandler::BeltRemoteControllerCommandHandler(int delay)
  : remoteController(nullptr) {}

void BeltRemoteControllerCommandHandler::setController(BeltRemoteController* controller) {
  remoteController = controller;
}

void BeltRemoteControllerCommandHandler::handleCommand(const char* command) {
  if (remoteController != nullptr) {
      Serial.println(command);

    if (command == "Forward") {
      remoteController->getBeltDriver().moveRight();
    } else if (command == "Backward") {
      remoteController->getBeltDriver().moveLeft();
    } else if (command == "Stop") {
      if (remoteController->getBeltDriver().getIsRunning()) {
        remoteController->getBeltDriver().stopMotor();
        Serial.print("Stepper stopped");
      } else {
        remoteController->getBeltDriver().startMotor();
        Serial.print("Stepper started");
      }
    }
  }
}
