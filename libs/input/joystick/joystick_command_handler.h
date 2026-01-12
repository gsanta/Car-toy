#ifndef JOYSTICK_COMMAND_HANDLER_H
#define JOYSTICK_COMMAND_HANDLER_H

class JoystickCommandHandler {
public:
    virtual void handleMove(int xVal, int yVal) = 0;
    virtual void handleClick(int buttonState) = 0;
    virtual ~JoystickCommandHandler() {}
};

#endif