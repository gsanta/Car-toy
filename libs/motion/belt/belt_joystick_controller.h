#ifndef BELT_JOYSTICK_CONTROLLER_H
#define BELT_JOYSTICK_CONTROLLER_H

#include <Arduino.h>
#include "../../input/joystick/staged_joystick_manager.h"
#include "../../input/joystick/staged_joystick_reader.h"
#include "../../input/joystick/joystick.h"

class BeltDriver;
// class StagedJoystickManager;
// class BeltJoystickController;

// class BeltJoystickControllerCommandHandler : public StagedJoystickReader {
// private:
//   BeltJoystickController* joystickController;

// public:
//   BeltJoystickControllerCommandHandler() : joystickController(nullptr) {}
  
//   void setController(BeltJoystickController* controller) {
//     joystickController = controller;
//   }
  
//   void handleMove(int xVal, int yVal) override;
//   void handleClick(int buttonState) override;
// };

class BeltJoystickController : public StagedJoystickReader {
public:
  BeltJoystickController(BeltDriver& beltDriver, Joystick& joystick);
  ~BeltJoystickController();

  void handleStagedMove(int xStage, int yStage) override;
    
private:
    BeltDriver& beltDriver;
    StagedJoystickManager& joystickManager;

    BeltDriver& getBeltDriver();

    int maxSpeed = 3;
};

#endif // BELT_JOYSTICK_CONTROLLER_H
