#include <Arduino.h>
#include "WiFi.h"
#include "ESP32_AsyncUDPServer.h"

void setup() {
  Serial.begin(115200);
  delay(2000);

  setupAsyncUDPServer();
}

void loop() {
  loopAsyncUDPServer();
}	
