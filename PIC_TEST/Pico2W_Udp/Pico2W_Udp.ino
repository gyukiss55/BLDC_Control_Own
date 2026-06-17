
#include <Arduino.h>
#include "Pico2W_UDPserver.h"
#include "WireCustom.h"

void setup() {
  Serial.begin(115200);
  delay(2000); // Wait for serial to initialize
  setupWire();
  setupUDPServer();
}

void loop() {
  loopUDPServer();
}

