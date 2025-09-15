#ifndef MOTOR_COMMAND_HANDLER_H
#define MOTOR_COMMAND_HANDLER_H

#include <Arduino.h>
#include "command_handler.h"
#include "motor_driver.h"
#include <Adafruit_MotorShield.h>
#include "directions.h"


class MotorCommandHandler : public CommandHandler {
  public:
    MotorCommandHandler(MotorDriver& driver) : motorDriver(driver) {}

    void handleCommand(const char* command);

  private:
    MotorDriver& motorDriver;
};

#endif
