#include "stepper_motor_radio_controller.h"

StepperMotorRadioController::StepperMotorRadioController(MotorDriverA4988& motor, uint8_t controlDirection) 
    : RadioReadCommandHandler(), motor(motor), controlDirection(controlDirection) {
}

void StepperMotorRadioController::handleMessageReceived(const char* message) {
    if (strncmp(message, "Move", 4) != 0) {
      return;  // Ignore messages that don't start with "Move"
    }


    int xStage, yStage;
    sscanf(message, "Move X Stage: %d, Y Stage: %d", &xStage, &yStage);

    int stage = (controlDirection == CONTROL_X) ? xStage : yStage;

    // Set speed based on yVal (0 = don't set, 1 or 2 = set speed)
    if (stage == 0) {
      motor.setIsRunning(false);
    } else {
      motor.setIsRunning(true);

      int speed = abs(stage);

      if (stage > 0) {
        motor.setDirection(UP);
      } else if (stage < 0) {
        motor.setDirection(DOWN);
      }

      Serial.println(speed);

      motor.setSpeed(speed);
    }
  };