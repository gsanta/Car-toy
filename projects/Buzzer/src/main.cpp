#include <Arduino.h>

// Passive buzzer connected to GPIO 5
const int BUZZER_PIN = 5;
const int PWM_CHANNEL = 0;  // PWM channel (0-15)
const int RESOLUTION = 8;    // 8-bit resolution

// Note frequencies (in Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

void playTone(int frequency, int duration) {
  if (frequency > 0) {
    ledcWriteTone(PWM_CHANNEL, frequency);
    delay(duration);
  }
  ledcWriteTone(PWM_CHANNEL, 0);  // Stop tone
}

void setup() {
  Serial.begin(115200);
  
  // Configure PWM for the buzzer
  ledcSetup(PWM_CHANNEL, 2000, RESOLUTION);  // 2kHz base frequency, 8-bit resolution
  ledcAttachPin(BUZZER_PIN, PWM_CHANNEL);
  
  Serial.println("Passive Buzzer Demo - ESP32");
}

void loop() {
  // Play a simple melody
  Serial.println("Playing melody...");
  
  playTone(NOTE_C4, 300);
  delay(100);
  playTone(NOTE_E4, 300);
  delay(100);
  playTone(NOTE_G4, 300);
  delay(100);
  playTone(NOTE_C5, 500);
  delay(500);
  
  // Play a siren effect
  Serial.println("Playing siren...");
  for (int i = 0; i < 3; i++) {
    for (int freq = 400; freq <= 800; freq += 10) {
      ledcWriteTone(PWM_CHANNEL, freq);
      delay(10);
    }
    for (int freq = 800; freq >= 400; freq -= 10) {
      ledcWriteTone(PWM_CHANNEL, freq);
      delay(10);
    }
  }
  ledcWriteTone(PWM_CHANNEL, 0);
  
  delay(2000);  // Wait before repeating
}