#include "timer/timer_control.h"
#include "MotionDetector/motion_detector.h"
#include "MotionDetector/motion_detector_timer_adapter.h"

TimerControl timer;
MotionDetector motionDetector(5);
MotionDetectorTimerAdapter motionAdapter(&motionDetector);

void setup() {
  Serial.begin(9600);
  delay(1000);
  motionDetector.setup();
  Serial.println("\n--- Motion detector set up ---");
  timer.add_millisecond_handler(&motionAdapter, 1000);
}

void loop() {
  timer.loop();
}