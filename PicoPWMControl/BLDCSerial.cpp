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
        Serial.print(" | RPS: ");
        Serial.print(hallCounterPerMin);
        Serial.print(" | RPSV: ");
		int firstIndex = hallCounterVectorIndex;
        for(int i = 0; i < 60; i++) {
			int j = (firstIndex + i) % 60;
            Serial.print(hallCounterVector[j]);
			if (i < 59)
                Serial.print(",");
		}
        Serial.println();
    }
}