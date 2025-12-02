#include "arduino_wifi_manager.h"

ArduinoWiFiManager::ArduinoWiFiManager(const char* ssid, const char* password, const char* server, int port) {
  this->ssid = ssid;
  this->password = password;
  this->server = server;
  this->port = port;
}

bool ArduinoWiFiManager::connect() {
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

bool ArduinoWiFiManager::sendHttpRequest(float temperature, float humidity) {
  if (client.connect(server, port)) {
    Serial.println("Connected to server");
    
    // Build GET request with query parameters
    String url = "/api/data?temperature=" + String(temperature, 1) + "&humidity=" + String(humidity, 1);
    
    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(server) + "\r\n");
    client.print("Connection: close\r\n\r\n");
    
    // Wait for response
    while (client.connected() && !client.available()) {
      delay(10);
    }
    
    // Read response
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
    
    client.stop();
    Serial.println("Request completed");
    
    return true;
  } else {
    Serial.println("Connection failed");
    return false;
  }
}
