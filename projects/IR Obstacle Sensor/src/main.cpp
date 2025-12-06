#include <Arduino.h>

#define IR_SENSOR_PIN 5

void setup() {
  Serial.begin(9600);
  
  // Configure IR sensor pin as input
  pinMode(IR_SENSOR_PIN, INPUT);
  
  Serial.println("IR Obstacle Avoidance Sensor Initialized");
  Serial.println("Sensor Pin: D5 (GPIO5)");
}

void loop() {
  // Read sensor value
  int sensorValue = digitalRead(IR_SENSOR_PIN);
  
  // Debug: Print the raw sensor value
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" -> ");
  
  // IR sensor outputs LOW when obstacle detected, HIGH when clear
  if (sensorValue == LOW) {
    Serial.println("OBSTACLE DETECTED!");
  } else {
    Serial.println("Path clear");
  }
  
  delay(500);  // Read every 500ms
}