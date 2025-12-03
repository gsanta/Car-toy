#ifndef MOTION_DETECTOR_TIMER_ADAPTER_H
#define MOTION_DETECTOR_TIMER_ADAPTER_H

#include "../system/timer/timer_handler.h"
#include "motion_detector.h"

class MotionDetectorTimerAdapter : public TimerHandler {
public:
    MotionDetectorTimerAdapter(class MotionDetector* detector) : detector(detector) {}

    void handleTimerEvent() override {
        detector->read();
    }

private:
    class MotionDetector* detector;
};

#endif
