#include "esp32_wifi_manager.h"

ESP32WiFiManager::ESP32WiFiManager(const char* ssid, const char* password, const char* server, int port) {
  this->ssid = ssid;
  this->password = password;
  this->server = server;
  this->port = port;
}

bool ESP32WiFiManager::connect() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  return true;
}

bool ESP32WiFiManager::sendHttpRequest(float temperature, float humidity) {
  HTTPClient http;
  
  // Build URL with query parameters
  String url = "http://" + String(server);
  if (port != 80) {
    url += ":" + String(port);
  }
  url += "/api/data?temperature=" + String(temperature, 1) + "&humidity=" + String(humidity, 1);
  
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    http.end();
    return true;
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    http.end();
    return false;
  }
}
