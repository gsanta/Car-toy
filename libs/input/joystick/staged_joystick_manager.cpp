#include <Arduino.h>
#include "staged_joystick_manager.h"
#include "joystick_command_handler.h"

StagedJoystickManager::StagedJoystickManager(int xPin, int yPin, int buttonPin, TimerControl& timerControl): joystick(xPin, yPin, buttonPin), timerControl(timerControl), timerListener(*this) {}

void StagedJoystickManager::setup() {
  joystick.setup();
  timerControl.add_millisecond_handler(&timerListener);
}

void StagedJoystickManager::addCommandHandler(JoystickCommandHandler *handler) {
  if (handlerCount < MAX_COMMAND_HANDLERS) {
      handlers[handlerCount++] = handler;
  }
}

int StagedJoystickManager::calculateStage(int value, int minVal, int maxVal) const {
  int range = maxVal - minVal;
  int center = minVal + range / 2;
  int stageSize = range / 5;
  
  if (value < center - stageSize) {
    if (value < center - 2 * stageSize) {
      return -2;
    }
    return -1;
  } else if (value > center + stageSize) {
    if (value > center + 2 * stageSize) {
      return 2;
    }
    return 1;
  }
  return 0;
}

void StagedJoystickManager::updateStages() {
  xStage = calculateStage(joystick.getXVal(), joystick.getXMin(), joystick.getXMax());
  yStage = calculateStage(joystick.getYVal(), joystick.getYMin(), joystick.getYMax());
}

void StagedJoystickManager::update() {
  joystick.read();
  updateStages();
  
  if (xStage != previousXStage || yStage != previousYStage) {
    for (int i = 0; i < handlerCount; ++i) {
      handlers[i]->handleMove(xStage, yStage);
    }
    previousXStage = xStage;
    previousYStage = yStage;
  }
  
  int currentButtonState = joystick.getButtonState();
  if (currentButtonState != previousButtonState) {
    for (int i = 0; i < handlerCount; ++i) {
      handlers[i]->handleClick(currentButtonState);
    }
    previousButtonState = currentButtonState;
  }
}