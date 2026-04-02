#include <Arduino.h>
#include "BLDCPWMControl.h"
#include "BLDCSerial.h"
#include "BLDCExternalInterrupt.h"
#include "BLDCPWMNet.h"


void setup() {
  BLDCSerial_init();
  BLDCExternalInterrupt_init();
  BLDCPWMControl_init();
  BLDCPWMNet_init();
}

void loop() {
  BLDCPWMNet_loop();
  BLDCPWMControl_loop();
  BLDCExternalInterrupt_loop();
  BLDCSerial_loop();
}