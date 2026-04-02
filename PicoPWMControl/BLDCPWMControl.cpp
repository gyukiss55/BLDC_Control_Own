// BLDCPWMControl.cpp

#include "BLDCPWMControl.h"

#include <Arduino.h>

#include "CommonData.h"

#define ESC_PIN 15

const int pwmPin = 15;
const int period_us = 20000; // 20 ms (50 Hz)
int lastSpeed = 0;

void BLDCPWMControl_init() {
	pinMode(ESC_PIN, OUTPUT);
	analogWriteFreq(100);        // 100 Hz
	analogWriteRange(65535);    // 16-bit resolution
}

void writeESC_donotuseit(int val) {
	// map 6553–13107 → 1000–2000 µs
	int pulse = map(val, 6553, 13107, 1000, 2000);

	digitalWrite(ESC_PIN, HIGH);
	delayMicroseconds(pulse);
	digitalWrite(ESC_PIN, LOW);
	delay(20 - pulse / 1000); // ~50Hz
}

void BLDCPWMControl_loop() {
	if (speed != lastSpeed) {
		analogWrite(pwmPin, speed);
		lastSpeed = speed;
		Serial.println("Updated PWM: " + String(speed));
	}
}