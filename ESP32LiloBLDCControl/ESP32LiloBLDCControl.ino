#include <Arduino.h>
#include "BLDCPort.h"

void setup() {
    Serial.begin(115200);
	delay(1000); // Wait for serial to initialize
    setupBLDCPort();

    setBLDCPeriod(1000000);   // 1000ms per commutation step
    setBLDCPWM(512);       // 50% duty
	Serial.println("Starting BLDC control V0.81");
}

void loop() {
    // Not used (FreeRTOS handles everything)
}