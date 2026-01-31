#include "./staged_joystick_reader.h"

int StagedJoystickReader::calculateStage(int value, int minVal, int maxVal) const {
  int range = maxVal - minVal;
  int center = minVal + range / 2;
  int stageSize = range / (2 * stages + 1);
  
  // Calculate which stage the value falls into
  int offset = value - center;
  
  // Determine the stage based on offset from center
  for (int i = stages; i >= 1; i--) {
    if (offset <= -(i * stageSize + stageSize / 2)) {
      return -i;
    }
  }
  
  for (int i = 1; i <= stages; i++) {
    if (offset >= (i * stageSize - stageSize / 2)) {
      if (i == stages || offset < ((i + 1) * stageSize - stageSize / 2)) {
        return i;
      }
    }
  }
  
  return 0;
}

void StagedJoystickReader::handleMove(int xVal, int yVal) {
  int xStage = calculateStage(xVal, joystick.getXMin(), joystick.getXMax());
  int yStage = calculateStage(yVal, joystick.getYMin(), joystick.getYMax());
  handleStagedMove(xStage, yStage);
}