#ifndef MOTOR_COMMAND_HANDLER_H
#define MOTOR_COMMAND_HANDLER_H

#include <Arduino.h>
#include "../../input/command_handler.h"
#include "../../system/directions.h"
#include "stepper_motor_driver.h"


class StepperCommandHandler : public CommandHandler {
  public:
    StepperCommandHandler(StepperMotorDriver& driver) : motorDriver(driver) {}

    void handleCommand(const char* command);

  private:
    StepperMotorDriver& motorDriver;
};

#endif
