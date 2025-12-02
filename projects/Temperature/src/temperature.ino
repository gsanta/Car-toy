#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "wifi_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi configuration
WiFiManager wifiManager("Vodafone-7342", "eUEgdRmpgdnhBam6", "192.168.0.107", 3000);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Connect to WiFi
  wifiManager.connect();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read DHT11");
    return;
  }

  // Round to 1 decimal
  float t1 = round(t * 10) / 10.0;
  float h1 = round(h * 10) / 10.0;

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

  // Send HTTP request
  wifiManager.sendHttpRequest(t1, h1);

  delay(2000);
}
