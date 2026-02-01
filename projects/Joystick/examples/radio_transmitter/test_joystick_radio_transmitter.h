#ifndef TEST_JOYSTICK_RADIO_TRANSMITTER_H
#define TEST_JOYSTICK_RADIO_TRANSMITTER_H

#include "../../../libs/input/joystick/staged_joystick_reader.h"
#include "../../../libs/system/timer/timer_handler.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"

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
      snprintf(text, sizeof(text), "X Stage: %d, Y Stage: %d", xStage, yStage);
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

#endif
