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
  if (read) {
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
  } else {
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
  }
}

bool RF24RadioTransmitter::read() {
  if (radio.available()) {
    radio.read(&receivedText, sizeof(receivedText));
    return true;
  }
  return false;
}

void RF24RadioTransmitter::write(const char* text, size_t length) {
  radio.write(text, length);
}

const char* RF24RadioTransmitter::getReceivedText() {
  return receivedText;
}

const void RF24RadioTransmitter::clearReceivedText() {
  receivedText[0] = '\0';
}