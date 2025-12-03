#include "motion_detector.h"

MotionDetector::MotionDetector(uint8_t sensor_pin) : sensor_pin(sensor_pin) {
    motion_detected = false;
}

void MotionDetector::setup() {
    pinMode(sensor_pin, INPUT);
    motion_detected = false;
}

void MotionDetector::read() {
    motion_detected = digitalRead(sensor_pin) == HIGH;
}