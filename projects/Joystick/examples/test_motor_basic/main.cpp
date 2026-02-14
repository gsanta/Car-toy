#include <Arduino.h>

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4  // Connect Arduino Pin 4 to A4988 ENABLE

void setup() {
  Serial.begin(9600);
  Serial.println("Simple Motor Test - With ENABLE Control");
  Serial.println("========================================");
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  
  // ENABLE must be LOW to enable the driver
  digitalWrite(ENABLE_PIN, LOW);
  Serial.println("ENABLE set to LOW (motor enabled)");
  Serial.println("Motor should now feel locked/resistant to turn");
  
  delay(2000);
  
  // Set direction
  digitalWrite(DIR_PIN, HIGH);
  Serial.println("Direction set to HIGH");
  Serial.println("Starting pulses...\n");
  
  delay(1000);
}

void loop() {
  static int count = 0;
  
  // Step HIGH
  digitalWrite(STEP_PIN, HIGH);
  Serial.print("Step ");
  Serial.print(count++);
  Serial.println(" HIGH");
  delayMicroseconds(1000);  // 1ms HIGH
  
  // Step LOW
  digitalWrite(STEP_PIN, LOW);
  Serial.println("       LOW");
  delayMicroseconds(1000);  // 1ms LOW
  
  // Total: 2ms per step = 500 steps/second
}
