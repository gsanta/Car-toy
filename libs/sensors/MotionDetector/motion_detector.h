#ifndef MOTION_DETECTOR_H
#define MOTION_DETECTOR_H

#include <Arduino.h>

class MotionDetector {
public:
    MotionDetector(uint8_t sensor_pin);

    bool is_motion_detected();
    void setup();
    void read();

private:
    uint8_t sensor_pin;
    bool motion_detected;
};

#endif