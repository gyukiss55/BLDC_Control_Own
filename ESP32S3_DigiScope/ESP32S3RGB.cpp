// ESP32S3RGB.cpp
#include "ESP32S3RGB.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 48  // ESP32-S3  onboard RGB LED pin
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupESP32S3RGB() {
	strip.begin();
	strip.setBrightness(1);
	strip.clear();
	strip.show();
}

void setRGB(int brightness, int red, int green, int blue) {
	strip.setBrightness(brightness);
	strip.setPixelColor(0, strip.Color(red, green, blue));
//	strip.show();
//	Serial.printf("Color: %d,%d,%d\n", red, green, blue);
}

void setRGB(int red, int green, int blue) {
	strip.setPixelColor(0, strip.Color(red, green, blue));
//	strip.show();
//	Serial.printf("Color: %d,%d,%d\n", red, green, blue);
}

void setRGBBrigthness(int brightness) {
	strip.setBrightness(brightness);
}

void unitTestRGB() {
	for (int r = 0; r <= 255; r += 51) {
		for (int g = 0; g <= 255; g += 51) {
			for (int b = 0; b <= 255; b += 51) {
				setRGB(r, g, b);
				delay(100);
				Serial.print("RGB test:");
				Serial.print(r);
				Serial.print(",);
				Serial.print(g);
				Serial.print(",);
				Serial.println(b);

			}
		}
	}
}

