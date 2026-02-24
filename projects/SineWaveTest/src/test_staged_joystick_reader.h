#ifndef TEST_STAGED_JOYSTICK_READER_H
#define TEST_STAGED_JOYSTICK_READER_H

#include "../../../libs/input/joystick/staged_joystick_reader.h"
#include "../../../libs/system/timer/timer_handler.h"

class TestStagedJoystickReader : public TimerHandler, public StagedJoystickReader {
public:
  TestStagedJoystickReader(Joystick& joystick) 
    : TimerHandler(100), StagedJoystickReader(3, joystick), 
      lastXStage(0), lastYStage(0) {}

  void handleTimerEvent() override {
    handleMove(getJoystick().getXVal(), getJoystick().getYVal());
  }


  void handleClick(int buttonState) override {
    // No action needed for click in this test
  }

  void handleStagedMove(int xStage, int yStage) override {
    if (xStage != lastXStage || yStage != lastYStage) {
      Serial.print("Stage changed - X: ");
      Serial.print(xStage);
      Serial.print(", Y: ");
      Serial.println(yStage);
      
      lastXStage = xStage;
      lastYStage = yStage;
    }
  }

private:
  int lastXStage;
  int lastYStage;
};

#endif
