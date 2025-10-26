
#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include "command_handler.h"

#define MAX_COMMAND_HANDLERS 5

class ServoDriver {
  public:

     void setup_servo_driver();

     void receive_remote_control_signal();
}