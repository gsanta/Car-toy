#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "./joystick_command_handler.h"
#include "../../system/timer/timer_control.h"

class TimerControl;

#define MAX_COMMAND_HANDLERS 5

class Joystick {
  public:
    Joystick(int xPin, int yPin, int buttonPin);

    void setup();

    void addCommandHandler(JoystickCommandHandler *handler);

    void read();

    int getXVal() const;
    int getYVal() const;

    int getXMin() const;
    int getXMax() const;
    int getYMin() const;
    int getYMax() const;

    int getButtonState() const;

  private:              
    int xPin;
    int yPin;
    int buttonPin;

    int xVal = 0;
    int yVal = 0;
    int buttonState = 0;

    int xMin = 0;
    int xMax = 1023;
    int yMin = 0;
    int yMax = 1023;
};

#endif