#ifndef BELT_JOYSTICK_CONTROLLER_H
#define BELT_JOYSTICK_CONTROLLER_H

#include <Arduino.h>
#include "../../input/joystick/staged_joystick_manager.h"
#include "../../input/joystick/joystick_command_handler.h"

class BeltDriver;
class StagedJoystickManager;
class BeltJoystickController;

class BeltJoystickControllerCommandHandler : public JoystickCommandHandler {
private:
  BeltJoystickController* joystickController;

public:
  BeltJoystickControllerCommandHandler() : joystickController(nullptr) {}
  
  void setController(BeltJoystickController* controller) {
    joystickController = controller;
  }
  
  void handleMove(int xVal, int yVal) override;
  void handleClick(int buttonState) override;
};

class BeltJoystickController {
    friend class BeltJoystickControllerCommandHandler;
    
private:
    BeltDriver& beltDriver;
    StagedJoystickManager& joystickManager;
    BeltJoystickControllerCommandHandler commandHandler;

    BeltDriver& getBeltDriver();

public:
    BeltJoystickController(BeltDriver& beltDriver, StagedJoystickManager& joystickManager);
    ~BeltJoystickController();
};

#endif // BELT_JOYSTICK_CONTROLLER_H
