// BLDCExternalInterrupt.cpp
#include "BLDCExternalInterrupt.h"
#include <Arduino.h>

volatile uint32_t BLDCExternalInterrupt::lastTime = 0;
volatile uint32_t BLDCExternalInterrupt::period = 0;
volatile int BLDCExternalInterrupt::direction = 1;

void IRAM_ATTR BLDCExternalInterrupt::isr() {
    uint32_t now = micros();
    period = now - lastTime;
    lastTime = now;
}

void BLDCExternalInterrupt::begin(int pin) {
    attachInterrupt(digitalPinToInterrupt(pin), isr, RISING);
}

float BLDCExternalInterrupt::getRPM() {
    if (period == 0) return 0;
    return 60000000.0 / period; // RPM
}

int BLDCExternalInterrupt::getDirection() {
    return direction;
}
