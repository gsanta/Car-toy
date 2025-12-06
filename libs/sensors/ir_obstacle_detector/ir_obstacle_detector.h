#ifndef IR_OBSTACLE_DETECTOR_H
#define IR_OBSTACLE_DETECTOR_H

#include <Arduino.h>

class IRObstacleDetector {
public:
    IRObstacleDetector(uint8_t sensor_pin);

    bool is_obstacle_detected();
    void setup();
    void read();

private:
    uint8_t sensor_pin;
    bool obstacle_detected;
};

#endif