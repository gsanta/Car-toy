#include <Arduino.h>
#include "joystick_updater.h"
#include "joystick_command_handler.h"

JoystickUpdater::JoystickUpdater(Joystick& joystick, TimerControl& timerControl): joystick(joystick), timerControl(timerControl), timerListener(*this) {}

void JoystickUpdater::setup() {
  joystick.setup();
  timerControl.add_millisecond_handler(&timerListener);
}

// void JoystickUpdater::addCommandHandler(JoystickCommandHandler *handler) {
//   if (handlerCount < MAX_COMMAND_HANDLERS) {
//       handlers[handlerCount++] = handler;
//   }
// }

// int JoystickUpdater::calculateStage(int value, int minVal, int maxVal) const {
//   int range = maxVal - minVal;
//   int center = minVal + range / 2;
//   int stageSize = range / 5;
  
//   if (value < center - stageSize) {
//     if (value < center - 2 * stageSize) {
//       return -2;
//     }
//     return -1;
//   } else if (value > center + stageSize) {
//     if (value > center + 2 * stageSize) {
//       return 2;
//     }
//     return 1;
//   }
//   return 0;
// }

// void JoystickUpdater::updateStages() {
//   xStage = calculateStage(joystick.getXVal(), joystick.getXMin(), joystick.getXMax());
//   yStage = calculateStage(joystick.getYVal(), joystick.getYMin(), joystick.getYMax());
// }

void JoystickUpdater::update() {
  joystick.read();
  // updateStages();
  
  // if (xStage != previousXStage || yStage != previousYStage) {
  // for (int i = 0; i < handlerCount; ++i) {
  //   handlers[i]->handleMove(xStage, yStage);
  // }
  //   previousXStage = xStage;
  //   previousYStage = yStage;
  // }
  
  // int currentButtonState = joystick.getButtonState();
  // if (currentButtonState != previousButtonState) {
  //   for (int i = 0; i < handlerCount; ++i) {
  //     handlers[i]->handleClick(currentButtonState);
  //   }
  //   previousButtonState = currentButtonState;
  // }
}