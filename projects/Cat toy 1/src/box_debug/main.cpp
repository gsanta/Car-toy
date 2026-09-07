#include <Arduino.h>
#include "../../lib/system/timer/timer_control.h"
#include "../../lib/motors/stepper_motor/motor_driver_a4988.h"
#include "../../lib/motors/stepper_motor/stepper_motor_timer_adapter.h"
// #include "../../lib/communication/radio_transmitter/rf24_radio_transmitter_manager.h"
// #include "../../lib/motors/stepper_motor/stepper_motor_radio_controller.h"

// Motor 1 pins (X axis)
constexpr uint8_t MOTOR_X_STEP_PIN = 4;
constexpr uint8_t MOTOR_X_DIR_PIN = 5;

// Motor 2 pins (Y axis)
constexpr uint8_t MOTOR_Y_STEP_PIN = 2;
constexpr uint8_t MOTOR_Y_DIR_PIN = 3;

// Debug motion profile
constexpr bool DIRECT_STEP_TEST = true;
constexpr int DEBUG_SPEED_MODE = 3;
constexpr unsigned long DIRECTION_FLIP_INTERVAL_MS = 5000;
constexpr unsigned long DIRECT_DIRECTION_FLIP_INTERVAL_MS = 4000;
constexpr unsigned int DIRECT_STEP_HIGH_US = 5;
constexpr unsigned int DIRECT_STEP_LOW_US = 700;
constexpr unsigned long STEP_REPORT_INTERVAL_MS = 500;
constexpr unsigned long MAPPING_SWITCH_INTERVAL_MS = 6000;

struct MotorPinMap {
  uint8_t stepPin;
  uint8_t dirPin;
  const char* label;
};

MotorPinMap pinMaps[] = {
  {4, 5, "X(4,5)"},
  {2, 3, "Y_box2(2,3)"},
  {3, 2, "Y_motor_test(3,2)"}
};

constexpr uint8_t PIN_MAP_COUNT = sizeof(pinMaps) / sizeof(pinMaps[0]);

// Global objects
TimerControl timerControl;
MotorDriverA4988 motorX(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
// MotorDriverA4988 motorY(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
StepperMotorTimerAdapter motorXAdapter(motorX);
// StepperMotorTimerAdapter motorYAdapter(motorY);
unsigned long lastDirectionFlipMs = 0;
bool isMovingUp = true;
unsigned long lastStepReportMs = 0;
unsigned long directStepCount = 0;
unsigned long lastMappingSwitchMs = 0;
uint8_t activeMapIndex = 0;

void selectActiveMap(uint8_t mapIndex) {
  activeMapIndex = mapIndex % PIN_MAP_COUNT;

  for (uint8_t i = 0; i < PIN_MAP_COUNT; i++) {
    pinMode(pinMaps[i].stepPin, OUTPUT);
    pinMode(pinMaps[i].dirPin, OUTPUT);
    digitalWrite(pinMaps[i].stepPin, LOW);
  }

  digitalWrite(pinMaps[activeMapIndex].dirPin, HIGH);
  isMovingUp = true;

  Serial.print("Active mapping: ");
  Serial.print(pinMaps[activeMapIndex].label);
  Serial.print(" STEP=");
  Serial.print(pinMaps[activeMapIndex].stepPin);
  Serial.print(" DIR=");
  Serial.println(pinMaps[activeMapIndex].dirPin);
}

// Radio transmitter (receiver) setup
// const byte address[5] = {0x30, 0x30, 0x30, 0x30, 0x31};
// RF24RadioTransmitterManager radioTransmitter(9, 8, address, timerControl);

// StepperMotorRadioController stepperMotorRadioController1(motorX, CONTROL_X);
// StepperMotorRadioController stepperMotorRadioController2(motorY, CONTROL_Y);


void setup() {
  Serial.begin(9600);
  Serial.print("CPU Frequency: ");
  Serial.println(F_CPU);
  Serial.println("Box Debug - Single Motor Test");
  if (DIRECT_STEP_TEST) {
    Serial.println("Mode: DIRECT_STEP_TEST");
    selectActiveMap(0);
  } else {
    Serial.print("Speed mode: ");
    Serial.println(DEBUG_SPEED_MODE);

    motorX.setDirection(UP);
    motorX.setSpeed(DEBUG_SPEED_MODE);
    motorX.setIsRunning(true);
    // motorY.setIsRunning(false);
    timerControl.add_microsecond_handler(&motorXAdapter);
    // timerControl.add_microsecond_handler(&motorYAdapter);
  }

  lastDirectionFlipMs = millis();
  lastStepReportMs = millis();
  lastMappingSwitchMs = millis();
  
  // Radio disabled in box_debug.
  // radioTransmitter.setup(true);

  // radioTransmitter.addCommandHandler(&stepperMotorRadioController1);
  // radioTransmitter.addCommandHandler(&stepperMotorRadioController2);
  // Serial.println("Radio receiver initialized");
}

void loop() {
  if (DIRECT_STEP_TEST) {
    MotorPinMap activeMap = pinMaps[activeMapIndex];

    digitalWrite(activeMap.stepPin, HIGH);
    delayMicroseconds(DIRECT_STEP_HIGH_US);
    digitalWrite(activeMap.stepPin, LOW);
    delayMicroseconds(DIRECT_STEP_LOW_US);
    directStepCount++;

    unsigned long now = millis();
    if (MAPPING_SWITCH_INTERVAL_MS > 0 && now - lastMappingSwitchMs >= MAPPING_SWITCH_INTERVAL_MS) {
      selectActiveMap(activeMapIndex + 1);
      directStepCount = 0;
      lastStepReportMs = now;
      lastDirectionFlipMs = now;
      lastMappingSwitchMs = now;
      return;
    }

    if (DIRECT_DIRECTION_FLIP_INTERVAL_MS > 0 && now - lastDirectionFlipMs >= DIRECT_DIRECTION_FLIP_INTERVAL_MS) {
      isMovingUp = !isMovingUp;
      digitalWrite(activeMap.dirPin, isMovingUp ? HIGH : LOW);
      lastDirectionFlipMs = now;
      Serial.println(isMovingUp ? "Direction: UP" : "Direction: DOWN");
    }

    if (now - lastStepReportMs >= STEP_REPORT_INTERVAL_MS) {
      Serial.print("Steps in last 500ms: ");
      Serial.println(directStepCount);
      directStepCount = 0;
      lastStepReportMs = now;
    }
    return;
  }

  timerControl.loop();

  if (DIRECTION_FLIP_INTERVAL_MS > 0 && millis() - lastDirectionFlipMs >= DIRECTION_FLIP_INTERVAL_MS) {
    isMovingUp = !isMovingUp;
    motorX.setDirection(isMovingUp ? UP : DOWN);
    lastDirectionFlipMs = millis();
  }
}
