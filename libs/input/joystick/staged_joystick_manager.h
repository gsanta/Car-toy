#ifndef STAGED_JOYSTICK_MANAGER_H
#define STAGED_JOYSTICK_MANAGER_H

#include "../../system/timer/timer_control.h"
#include "./joystick_command_handler.h"
#include "./joystick.h"

#define MAX_COMMAND_HANDLERS 5

class Joystick;
class StagedJoystickManager;

class JoystickTimerListener : public TimerHandler {
private:
  StagedJoystickManager& manager;

public:
  JoystickTimerListener(StagedJoystickManager& manager);

  void handleTimerEvent() override;
};


class StagedJoystickManager {
  friend class JoystickTimerListener;

  public:
    StagedJoystickManager(int xPin, int yPin, int buttonPin, TimerControl& timerControl);

    void addCommandHandler(JoystickCommandHandler *handler);

    void setup();

  private:
    int calculateStage(int value, int minVal, int maxVal) const;

    void updateStages();
    void update();

    Joystick joystick;
    TimerControl& timerControl;
    JoystickTimerListener timerListener;

    int xStage = 0;
    int yStage = 0;
    int previousXStage = 0;
    int previousYStage = 0;
    int previousButtonState = 0;

    JoystickCommandHandler* handlers[MAX_COMMAND_HANDLERS];
    int handlerCount;
};

inline JoystickTimerListener::JoystickTimerListener(StagedJoystickManager& manager) : TimerHandler(20), manager(manager) {}

inline void JoystickTimerListener::handleTimerEvent() {
  manager.update();
}

#endif