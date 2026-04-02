// BLDCSerial.cpp

#include "BLDCSerial.h"

#include <Arduino.h>

#include "CommonData.h"

unsigned long lastSerial = 0;

void BLDCSerial_init() {
    Serial.begin(115200);
	delay(2000); // Wait for serial to initialize
}

void BLDCSerial_loop() {
    if (millis() - lastSerial >= 1000) {
        lastSerial = millis();
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.print(" | Hall: ");
        Serial.print(hallCounter);
        Serial.print(" | RPM: ");
        Serial.println(hallCounterPerMin);
    }
}