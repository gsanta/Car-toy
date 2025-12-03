#include "timer/timer_control.h"
#include "MotionDetector/motion_detector.h"
#include "MotionDetector/motion_detector_timer_adapter.h"

TimerControl timer;
MotionDetector motionDetector(5);
MotionDetectorTimerAdapter motionAdapter(&motionDetector);

void setup() {
  motionDetector.setup();
  timer.add_millisecond_handler(&motionAdapter, 1000);
}

void loop() {
  timer.loop();

  //create a debug timer adapter in system/debug so we can print the motion status
}