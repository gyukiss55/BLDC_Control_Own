// BLDCExternalInterrupt.cpp

#include "BLDCExternalInterrupt.h"

#include "CommonData.h"
#include <Arduino.h>

#define HALL_PIN 16

unsigned long lastRPMCalc = 0;
unsigned long lastHallCounter = 0;

void hallISR () {
    hallCounter++;
}

void BLDCExternalInterrupt_init() {
    pinMode(HALL_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(HALL_PIN), hallISR, RISING);
}

void BLDCExternalInterrupt_loop() {
    if (millis() - lastRPMCalc >= 100) {
        lastRPMCalc = millis();
		int hallCounterNow = hallCounter;
        hallCounterPerMin = (hallCounterNow - lastHallCounter);
		hallCounterVector[hallCounterVectorIndex] = hallCounterPerMin;
		hallCounterVectorIndex = (hallCounterVectorIndex + 1) % 60;
        lastHallCounter = hallCounterNow;
    }
}