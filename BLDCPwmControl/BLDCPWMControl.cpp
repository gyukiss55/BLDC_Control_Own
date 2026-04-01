// BLDCPWMControl.cpp

#include "BLDCPWMControl.h"
#include <Arduino.h>

void BLDCPWMControl::begin(int pin) {
    pwmPin = pin;

    ledcAttach(pwmPin, 50, 16); // 50 Hz, 16-bit
}

void BLDCPWMControl::setPWM(int period_us, int duty_us) {
    // Convert µs to duty (16-bit)
    float duty = (float)duty_us / period_us;
    uint32_t value = duty * 65535;

    ledcWrite(pwmPin, value);
}