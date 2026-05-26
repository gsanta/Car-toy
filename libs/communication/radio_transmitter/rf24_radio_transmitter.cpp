#include "rf24_radio_transmitter.h"
#include <string.h>

RF24RadioTransmitter::RF24RadioTransmitter(uint8_t ce, uint8_t csn, const byte* addr)
  : radio(ce, csn), cePin(ce), csnPin(csn) {
  memcpy(address, addr, 6);
  receivedText[0] = '\0';
}

RF24RadioTransmitter::~RF24RadioTransmitter() {
  // Destructor implementation
}

void RF24RadioTransmitter::setup(bool read) {
  radio.begin();

  delay(500);

    Serial.println("[RF24] Attempting to initialize...");
  
  // Add extra delays for Arduino clones with timing issues
  delay(100);
  
  // Try with retries
  int retries = 0;
  while (retries < 3 && !radio.begin()) {
    Serial.print("[RF24] Init failed (attempt ");
    Serial.print(retries + 1);
    Serial.println("), retrying...");
    delay(100);
    radio.powerDown();
    delay(100);
    retries++;
  }

    if (retries >= 3) {
    Serial.println("[RF24] Init failed after 3 attempts - possible hardware issue");
    Serial.println("[RF24] For new Arduino clones, check:");
    Serial.println("  - Oscillator frequency (should be 16MHz)");
    Serial.println("  - RF24 power supply (add 10µF capacitor near VCC)");
    return;
  }
  
  Serial.println("[RF24] Init success");
  
  // radio.setChannel(76);
  // radio.setDataRate(RF24_1MBPS);
  // radio.disableDynamicPayloads();
  // radio.setPayloadSize(32);

  if (read) {
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
    Serial.println("[RF24] Setup as RECEIVER");
  } else {
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
    Serial.println("[RF24] Setup as TRANSMITTER");
  }
  
  Serial.print("[RF24] Channel: ");
  Serial.println(radio.getChannel());
  Serial.print("[RF24] DataRate: ");
  Serial.println(radio.getDataRate());
}

bool RF24RadioTransmitter::read() {
  if (radio.available()) {
    radio.read(&receivedText, sizeof(receivedText));

    // radio.read(receivedText, 32);
    // receivedText[32] = '\0';  // Null terminate
    return true;
  }
  return false;
}

void RF24RadioTransmitter::write(const char* text, size_t length) {
  // Pad to exactly 32 bytes
  // char buffer[32] = {0};
  // memcpy(buffer, text, (length > 32) ? 32 : length);
  
  // Serial.print("[RF24] Sending: ");
  // Serial.println(text);
  // radio.write(buffer, 32);
  radio.write(text, length);
}

const char* RF24RadioTransmitter::getReceivedText() {
  return receivedText;
}

const void RF24RadioTransmitter::clearReceivedText() {
  receivedText[0] = '\0';
}