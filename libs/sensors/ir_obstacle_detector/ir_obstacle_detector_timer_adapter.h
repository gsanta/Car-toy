#ifndef IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H
#define IR_OBSTACLE_DETECTOR_TIMER_ADAPTER_H

#include "../system/timer/timer_handler.h"
#include "ir_obstacle_detector.h"

class IRObstacleDetectorTimerAdapter : public TimerHandler {
public:
    IRObstacleDetectorTimerAdapter(class IRObstacleDetector* detector) : detector(detector) {}

    void handleTimerEvent() override {
        detector->read();
    }

private:
    class IRObstacleDetector* detector;
};

#endif
