#ifndef JOYSTICK_COMMAND_DIRECTOR_H
#define JOYSTICK_COMMAND_DIRECTOR_H

#include <Arduino.h>
#include "../../lib/input/joystick/joystick.h"
#include "../../lib/input/joystick/staged_joystick_reader.h"
#include "../../lib/system/timer/timer_handler.h"
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"

#define MOTOR_UP 1
#define MOTOR_DOWN 2

class JoystickCommandDirector : public TimerHandler, public StagedJoystickReader {
public:
  JoystickCommandDirector(Joystick& joystick, MotorDriverA4988& motorX, MotorDriverA4988& motorY, TimerControl& timerControl) 
    : TimerHandler(100), StagedJoystickReader(3, joystick), motorX(motorX), motorY(motorY), timerControl(timerControl),
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
    // Keep only the dominant axis to avoid joystick cross-talk driving both motors.
    if (abs(xStage) > abs(yStage)) {
      yStage = 0;
    } else if (abs(yStage) > abs(xStage)) {
      xStage = 0;
    }

    if (xStage != lastXStage) {
      controlMotor(motorX, xStage);
      lastXStage = xStage;
      
      Serial.print("X Stage: ");
      Serial.println(xStage);
    }
    
    if (yStage != lastYStage) {
      controlMotor(motorY, yStage);
      lastYStage = yStage;
      
      Serial.print("Y Stage: ");
      Serial.println(yStage);
    }
  }

private:
  MotorDriverA4988& motorX;
  MotorDriverA4988& motorY;
  TimerControl& timerControl;
  
  int lastXStage;
  int lastYStage;
  
  int maxSpeed = 3;

  void controlMotor(MotorDriverA4988& motor, int stage) {
    // stage = 0: stop, > 0: UP, < 0: DOWN
    Serial.print("  controlMotor stage=");
    Serial.print(stage);
    Serial.print(" running=");
    if (stage == 0) {
      motor.setIsRunning(false);
      Serial.println("false");
    } else {
      motor.setIsRunning(true);
      
      int speed = abs(stage);
      
      if (stage > 0) {
        motor.setDirection(MOTOR_UP);
      } else if (stage < 0) {
        motor.setDirection(MOTOR_DOWN);
      }
      
      motor.setSpeed(speed);
      Serial.print("true dir=");
      Serial.print(stage > 0 ? "UP" : "DOWN");
      Serial.print(" speed=");
      Serial.println(speed);
    }
  }
};

#endif
