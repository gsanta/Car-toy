#include <Arduino.h>
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/input/joystick/joystick_updater.h"
#include "../../lib/input/joystick/staged_joystick_reader.h"
#include "../../lib/system/timer/timer_handler.h"

// Joystick pins
constexpr uint8_t JOYSTICK_X_PIN = A1;
constexpr uint8_t JOYSTICK_Y_PIN = A6;
constexpr uint8_t JOYSTICK_BUTTON_PIN = 6;

// Test command director that prints staged moves instead of driving motors
class TestJoystickCommandDirector : public TimerHandler, public StagedJoystickReader {
public:
  TestJoystickCommandDirector(Joystick& joystick, TimerControl& timerControl)
    : TimerHandler(100), StagedJoystickReader(3, joystick), timerControl(timerControl),
      lastXStage(0), lastYStage(0) {}

  void setup() {
    timerControl.add_millisecond_handler(this);
  }

  void handleTimerEvent() override {
    handleMove(getJoystick().getXVal(), getJoystick().getYVal());
  }

  void handleClick(int buttonState) override {
    // No action for button
  }

  void handleStagedMove(int xStage, int yStage) override {
    if (xStage != lastXStage) {
      Serial.print("X Stage: ");
      Serial.println(xStage);
      lastXStage = xStage;
    }
    
    if (yStage != lastYStage) {
      Serial.print("Y Stage: ");
      Serial.println(yStage);
      lastYStage = yStage;
    }
  }

private:
  TimerControl& timerControl;
  int lastXStage;
  int lastYStage;
};

// Global objects
TimerControl timerControl;
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, JOYSTICK_BUTTON_PIN);
JoystickUpdater joystickUpdater(joystick, timerControl);
TestJoystickCommandDirector testCommandDirector(joystick, timerControl);

void setup() {
  Serial.begin(9600);
  Serial.println("JOYSTICK TEST - Full setup with stage printing");
  Serial.println("Staged moves will be printed when joystick changes");
  
  joystickUpdater.setup();
  testCommandDirector.setup();
}

void loop() {
  timerControl.loop();  
}
