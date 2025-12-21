#include <Arduino.h>

// Passive buzzer connected to digital pin 9 (PWM capable)
const int BUZZER_PIN = 9;

// Note frequencies (in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659

void playTone(int frequency, int duration) {
  if (frequency > 0) {
    tone(BUZZER_PIN, frequency);
    delay(duration);
  }
  noTone(BUZZER_PIN);  // Stop tone
}

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Passive Buzzer Demo - Arduino Nano");
}

void loop() {
  // Play "Kiskarácsony, nagykarácsony" (Hungarian Christmas song)
  Serial.println("Playing Kiskaracsony, nagykaracsony...");
  
  // "Kis-ka-rá-csony, nagy-ka-rá-csony"
  playTone(NOTE_G4, 400);
  delay(50);
  playTone(NOTE_G4, 400);
  delay(50);
  playTone(NOTE_A4, 400);
  delay(50);
  playTone(NOTE_G4, 400);
  delay(50);
  playTone(NOTE_F4, 400);
  delay(50);
  playTone(NOTE_E4, 400);
  delay(50);
  playTone(NOTE_D4, 800);
  delay(200);
  
  // "Más-nap me-gyünk to-vább"
  playTone(NOTE_D4, 400);
  delay(50);
  playTone(NOTE_E4, 400);
  delay(50);
  playTone(NOTE_F4, 400);
  delay(50);
  playTone(NOTE_E4, 400);
  delay(50);
  playTone(NOTE_D4, 400);
  delay(50);
  playTone(NOTE_C4, 800);
  delay(200);
  
  // "Más-nap me-gyünk to-vább"
  playTone(NOTE_D4, 400);
  delay(50);
  playTone(NOTE_E4, 400);
  delay(50);
  playTone(NOTE_F4, 400);
  delay(50);
  playTone(NOTE_E4, 400);
  delay(50);
  playTone(NOTE_D4, 400);
  delay(50);
  playTone(NOTE_C4, 800);
  delay(500);
  
  delay(2000);  // Wait before repeating
}