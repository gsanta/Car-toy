#include "motor_command_handler.h"

void MotorCommandHandler::handleCommand(const char* command) {
  Serial.print("MotorCommandHandler received: ");
  Serial.println(command);

  if (command == "Forward") {
    motorDriver.run(FORWARD);
  } else if (command == "Backward") {
    motorDriver.run(BACKWARD);
  } else if (command == "Left") {
    motorDriver.turn(LEFT);
  } else if (command == "Right") {
    motorDriver.turn(RIGHT);
  } else if (command == "Stop") {
    motorDriver.run(RELEASE);
  }
}
