
#include "PicoBMP280.h"
#include "PicoMPU6500.h"

void setup() {
  Serial.begin(115200);
  setupPicoBMP280 ();
  setupPicoMPU6500 ();
}

void loop() {
  loopPicoBMP280 ();
  loopPicoMPU6500 ();
  
}