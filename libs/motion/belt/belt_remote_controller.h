#ifndef BELT_REMOTE_CONTROLLER_H
#define BELT_REMOTE_CONTROLLER_H

#include "belt_remote_controller_command_handler.h"
#include "../../input/remote_control/remote_control.h"

class TestJoystickRadioTransmitter : public TimerHandler, public StagedJoystickReader {
public:
  TestJoystickRadioTransmitter(Joystick& joystick, RF24RadioTransmitter& transmitter) 
    : TimerHandler(100), StagedJoystickReader(3, joystick), transmitter(transmitter),
      lastXStage(0), lastYStage(0) {}

  void handleTimerEvent() override {
    handleMove(getJoystick().getXVal(), getJoystick().getYVal());
  }


  void handleClick(int buttonState) override {
    // No action needed for click in this test
  }

  void handleStagedMove(int xStage, int yStage) override {
    if (xStage != lastXStage || yStage != lastYStage) {
      char text[32] = {0};
      snprintf(text, sizeof(text), "Move X Stage: %d, Y Stage: %d", xStage, yStage);
      transmitter.write(text, sizeof(text));
      Serial.print("Transmitted - ");
      Serial.println(text);
      
      lastXStage = xStage;
      lastYStage = yStage;
    }
  }

private:
  RF24RadioTransmitter& transmitter;

  int lastXStage;
  int lastYStage;
};
#endif // BELT_REMOTE_CONTROLLER_H
