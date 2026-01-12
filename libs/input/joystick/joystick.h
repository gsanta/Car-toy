#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "./joystick_command_handler.h"
#include "../../system/timer/timer_control.h"
#include "joystick_timer_listener.h"

class TimerControl;

#define MAX_COMMAND_HANDLERS 5

class Joystick {
  public:
    Joystick(int xPin, int yPin, int buttonPin);

    void setup();

    void addCommandHandler(JoystickCommandHandler *handler);

    void read();

  private:              
    int xPin;
    int yPin;
    int buttonPin;

    int xVal = 0;
    int yVal = 0;
    int buttonState = 0;

    JoystickCommandHandler* handlers[MAX_COMMAND_HANDLERS];
    int handlerCount;
};

#endif