#ifndef JOYSTICK_COMMAND_TRANSMITTER_H
#define JOYSTICK_COMMAND_TRANSMITTER_H

#include "../../../libs/input/joystick/staged_joystick_reader.h"
#include "../../../libs/system/timer/timer_handler.h"
#include "../../../libs/system/timer/timer_control.h"
#include "../../lib/communication/radio_transmitter/rf24_radio_transmitter.h"

class JoystickCommandTransmitter : public TimerHandler, public StagedJoystickReader {
public:
  JoystickCommandTransmitter(Joystick& joystick, RF24RadioTransmitter& transmitter, TimerControl& timerControl) 
    : TimerHandler(100), StagedJoystickReader(3, joystick), transmitter(transmitter), timerControl(timerControl),
      lastXStage(0), lastYStage(0) {}

  void setup() {
    timerControl.add_millisecond_handler(this);
  }

  void handleTimerEvent() override {
    handleMove(getJoystick().getXVal(), getJoystick().getYVal());
  }


  void handleClick(int buttonState) override {
    // No action needed for click right now
  }

  void handleStagedMove(int xStage, int yStage) override {
    if (xStage != lastXStage || yStage != lastYStage) {
      char text[32] = {0};
      snprintf(text, sizeof(text), "Move X Stage: %d, Y Stage: %d", xStage, yStage);
      transmitter.write(text, sizeof(text));
      
      lastXStage = xStage;
      lastYStage = yStage;
    }
  }

private:
  RF24RadioTransmitter& transmitter;
  TimerControl& timerControl;

  int lastXStage;
  int lastYStage;
};

#endif
