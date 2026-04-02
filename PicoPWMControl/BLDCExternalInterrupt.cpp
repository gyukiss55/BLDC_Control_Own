// BLDCExternalInterrupt.cpp

#include "BLDCExternalInterrupt.h"

#include "CommonData.h"
#include <Arduino.h>

#define HALL_PIN 16

unsigned long lastRPMCalc = 0;
unsigned long lastHallCounter = 0;
/*
void IRAM_ATTR hallISR() {
    hallCounter++;
}
*/

void BLDCExternalInterrupt_init() {
    pinMode(HALL_PIN, INPUT_PULLUP);
//    attachInterrupt(digitalPinToInterrupt(HALL_PIN), hallISR, RISING);
}

void BLDCExternalInterrupt_loop() {
    if (millis() - lastRPMCalc >= 1000) {
        hallCounterPerMin = (hallCounter  - lastHallCounter);
        lastHallCounter = hallCounter;
        lastRPMCalc = millis();
    }
}