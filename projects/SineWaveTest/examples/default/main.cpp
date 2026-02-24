#include <Arduino.h>
#include <math.h>
#include <driver/dac.h>

static const int kDacPin = 25; // or 26
static const int kTableSize = 256;
static uint8_t sineTable[kTableSize];

static dac_channel_t getDacChannel(int pin) {
  return (pin == 26) ? DAC_CHANNEL_2 : DAC_CHANNEL_1;
}

void setup() {
  dac_channel_t channel = getDacChannel(kDacPin);
  dac_output_enable(channel);

  for (int i = 0; i < kTableSize; ++i) {
    float angle = (2.0f * PI * i) / kTableSize;
    sineTable[i] = (uint8_t)((sinf(angle) + 1.0f) * 127.5f);
  }
}

void loop() {
  dac_channel_t channel = getDacChannel(kDacPin);
  for (int i = 0; i < kTableSize; ++i) {
    dac_output_voltage(channel, sineTable[i]);
    delayMicroseconds(20); // ~195 Hz output (1 / (256*20us))
  }
}
