#include <Arduino.h>

// Define motor pins
#define STEP_PIN 2
#define DIR_PIN 3

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n=================================");
  Serial.println("A4988 HARDWARE DIAGNOSTIC TEST");
  Serial.println("=================================\n");
  
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
  Serial.println("Test 1: Measure voltages with multimeter");
  Serial.println("------------------------------------------");
  Serial.println("Set DIR HIGH...");
  digitalWrite(DIR_PIN, HIGH);
  Serial.print("Pin ");
  Serial.print(DIR_PIN);
  Serial.println(" should show ~5V now");
  delay(3000);
  
  Serial.println("\nSet DIR LOW...");
  digitalWrite(DIR_PIN, LOW);
  Serial.print("Pin ");
  Serial.print(DIR_PIN);
  Serial.println(" should show ~0V now");
  delay(3000);
  
  Serial.println("\n\nTest 2: Very slow stepping (visible on LED)");
  Serial.println("--------------------------------------------");
  Serial.println("Connect an LED between Pin 2 and GND (with resistor)");
  Serial.println("Starting slow pulses in 3 seconds...\n");
  delay(3000);
}

void loop() {
  static int count = 0;
  
  Serial.print("Step ");
  Serial.print(count++);
  Serial.println(" - HIGH");
  digitalWrite(STEP_PIN, HIGH);
  delay(1000);  // 1 second HIGH
  
  Serial.println("        - LOW");
  digitalWrite(STEP_PIN, LOW);
  delay(1000);  // 1 second LOW
  
  if (count % 10 == 0) {
    Serial.println("\n=== HARDWARE CHECKLIST ===");
    Serial.println("If motor still not moving, check:");
    Serial.println("1. A4988 ENABLE pin - must be LOW or unconnected");
    Serial.println("2. A4988 VMOT - needs 8-35V power supply connected");
    Serial.println("3. A4988 GND - must connect to Arduino GND");
    Serial.println("4. Motor wires - try swapping 1A/1B or 2A/2B pairs");
    Serial.println("5. Motor power - is your power supply ON and adequate?");
    Serial.println("6. Use multimeter on STEP pin - should show 0V/5V\n");
  }
}
