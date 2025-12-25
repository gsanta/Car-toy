#include "stepper_command_handler.h"

void StepperCommandHandler::handleCommand(const char* command) {
  Serial.println(command);

  if (command == "Forward") {
    motorDriver.setDirection(UP);
  } else if (command == "Backward") {
    motorDriver.setDirection(DOWN);
  } else if (command == "Stop") {
    if (!motorDriver.isRunning()) {
      motorDriver.rotate();
      Serial.print("Stepper started");
    } else {
      motorDriver.stop();
      Serial.print("Stepper stopped");
    }
  }
}
