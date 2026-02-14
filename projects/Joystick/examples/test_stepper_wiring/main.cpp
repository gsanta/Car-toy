#include <Arduino.h>

// Define motor pins - same as your main program
#define STEP_PIN 2
#define DIR_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("Stepper Motor Wiring Test");
  Serial.println("========================");
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  // Set direction
  digitalWrite(DIR_PIN, HIGH);
  Serial.println("Direction set to HIGH (forward)");
  Serial.println("Starting motor test in 2 seconds...");
  delay(2000);
}

void loop() {
  // Generate pulses manually - very slow so you can see/measure with multimeter
  Serial.println("STEP HIGH");
  digitalWrite(STEP_PIN, HIGH);
  delay(500);  // 500ms - motor should move one step
  
  Serial.println("STEP LOW");
  digitalWrite(STEP_PIN, LOW);
  delay(500);  // 500ms delay between steps
  
  // After 20 steps, reverse direction
  static int stepCount = 0;
  stepCount++;
  
  if (stepCount >= 20) {
    Serial.println("\n=== REVERSING DIRECTION ===\n");
    digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));
    stepCount = 0;
    delay(1000);
  }
}
