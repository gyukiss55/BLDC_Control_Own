
#include <Arduino.h>
#include "Pico2W_UDPserver.h"

void setup() {
  Serial.begin(115200);
  setupUDPServer();
}

void loop() {
  loopUDPServer();
}

