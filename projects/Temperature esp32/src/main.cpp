#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "wifi_manager.h"
#include "esp32_wifi_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C pins for OLED
#define SDA_PIN 21
#define SCL_PIN 22
#define BUTTON_PIN 27

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT22
// #define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

ESP32WiFiManager wifiManagerImpl("Vodafone-7342", "eUEgdRmpgdnhBam6", "192.168.0.107", 3000);
WiFiManager* wifiManager = &wifiManagerImpl;

bool displayEnabled = true;
int lastButtonReading = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;

void updateDisplayButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime >= 50 && reading != buttonState) {
    buttonState = reading;

    if (buttonState == LOW) {
      displayEnabled = !displayEnabled;

      if (!displayEnabled) {
        display.clearDisplay();
        display.display();
      }
    }
  }

  lastButtonReading = reading;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n--- ESP32 Temperature Monitor Started ---");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Initializing DHT22 sensor...");
  dht.begin();

  // Initialize I2C with custom pins
  Serial.println("Initializing I2C for OLED...");
  Wire.begin(SDA_PIN, SCL_PIN);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    Serial.println("Try address 0x3D if you see a device at that address above");
    for (;;);
  }
  Serial.println("OLED display initialized successfully");

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  wifiManager->connect();
  Serial.println("Setup complete!\n");
}

void loop() {
  updateDisplayButton();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("ERROR: Failed to read DHT22 sensor!");
    Serial.println("Check wiring and connections\n");
    delay(2000);
    return;
  }

  // Round to 1 decimal
  float t1 = round(t * 10) / 10.0;
  float h1 = round(h * 10) / 10.0;


  if (displayEnabled) {
    display.clearDisplay();
    display.setTextSize(2);

    display.setCursor(0, 0);
    display.print("Tem: ");
    display.print(t1, 1);   // 1 decimal
    display.println("C");

    display.setCursor(0, 30);
    display.print("Hum: ");
    display.print(h1, 1);   // 1 decimal
    display.println("%");

    display.display();
  }

  // Send HTTP request
  wifiManager->sendHttpRequest(t1, h1);

  delay(2000);
}