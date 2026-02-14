#ifndef TEST_JOYSTICK_RADIO_TRANSMITTER_H
#define TEST_JOYSTICK_RADIO_TRANSMITTER_H

#include "../../../libs/input/joystick/staged_joystick_reader.h"
#include "../../../libs/system/timer/timer_handler.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/communication/radio_transmitter/radio_read_command_handler.h"

class ControlStepperMotorWithRadio : public TimerHandler, public RadioReadCommandHandler {
public:
  ControlStepperMotorWithRadio(MotorDriverA4988& motor, MotorDriverA4988& motor2) 
    : TimerHandler(100), RadioReadCommandHandler(), motor(motor), motor2(motor2) {}

  void handleTimerEvent() override {
  }

  void handleMessageReceived(const char* message) override {
    if (strncmp(message, "Move", 4) != 0) {
      return;  // Ignore messages that don't start with "Move"
    }


    int xStage, yStage;
    sscanf(message, "Move X Stage: %d, Y Stage: %d", &xStage, &yStage);

    // Set speed based on yVal (0 = don't set, 1 or 2 = set speed)
    if (xStage == 0) {
      motor.setIsRunning(false);
    } else {
      motor.setIsRunning(true);

      int speed = abs(xStage);

      if (xStage > 0) {
        motor.setDirection(UP);
      } else if (xStage < 0) {
        motor.setDirection(DOWN);
      }

      Serial.println(speed);

      motor.setSpeed(speed);
    }

        // Set speed based on yVal (0 = don't set, 1 or 2 = set speed)
    if (yStage == 0) {
      motor2.setIsRunning(false);
    } else {
      motor2.setIsRunning(true);

      int speed = abs(yStage);

      if (yStage > 0) {
        motor2.setDirection(UP);
      } else if (yStage < 0) {
        motor2.setDirection(DOWN);
      }

      motor2.setSpeed(speed);
    }
  };

private:
  MotorDriverA4988& motor;  
  MotorDriverA4988& motor2;

  int maxSpeed = 3;

  int lastXStage;
  int lastYStage;
};

#endif
