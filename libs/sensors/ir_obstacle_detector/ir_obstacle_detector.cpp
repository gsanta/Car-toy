#include "ir_obstacle_detector.h"

IRObstacleDetector::IRObstacleDetector(uint8_t sensor_pin) : sensor_pin(sensor_pin) {
    obstacle_detected = false;
}

void IRObstacleDetector::setup() {
    pinMode(sensor_pin, INPUT);
    obstacle_detected = false;
}

void IRObstacleDetector::read() {
    obstacle_detected = digitalRead(sensor_pin) == LOW;
}