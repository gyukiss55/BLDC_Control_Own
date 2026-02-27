#include <Arduino.h>
#include "BLDCPort.h"
#include "BLDCSerial.h"

void setup() {
    setupSerial();
    setupBLDCPort();

    setBLDCPeriod(1000000);   // 1000ms per commutation step
    setBLDCPWM(512);       // 50% duty
	Serial.println("Starting BLDC control V0.81");
}

void loop() {
    // Not used (FreeRTOS handles everything)
    loopBLDCPort ();
    SerialInputLoop();
}