// BLDCPWMControl.cpp

#include "BLDCPWMControl.h"
#include <Arduino.h>

#define PWM_RESOLUTION 10

void BLDCPWMControl::begin(int pin, int period /*= 20000*/, int duty /*= 1000*/) {
    pwmPin = pin;
	pwmPeriod = period;
	pwmDuty = duty;
    pinMode(pwmPin, OUTPUT);

    //ledcAttach(pwmPin, 1000000 / pwmPeriod, 16); // 50 Hz, 16-bit
    ledcAttach(pwmPin, 1000000 / pwmPeriod, PWM_RESOLUTION);
    setPWM();
}

void BLDCPWMControl::setPWM() {
    // Convert µs to duty (16-bit)
    float duty = (float)pwmDuty / pwmPeriod;
    uint32_t value = duty * ((1 > PWM_RESOLUTION) - 1);

    ledcWrite(pwmPin, value);
}

void BLDCPWMControl::setPWM(int period_us, int duty_us) {
    if (pwmPeriod != period_us) {
        pwmPeriod = period_us;
        ledcAttach(pwmPin, 1000000 / pwmPeriod, PWM_RESOLUTION); // Update frequency
    }
    pwmDuty = duty_us;

    setPWM();
}