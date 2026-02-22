// ESP32C3DigiOutput.cpp
#include "ESP32C3DigiOutput.h"
#include "ESP32S3RGB.h"


int digitOutputPins[] = { 37, 38, 39, 40, 41, 42}; // Example GPIO pins for digital input

void setupESP32C3DigiOutput()
{
	// Configure GPIOs for digital output (example: GPIO0-GPIO7)
	for (int pin = 0;  digitOutputPins[pin] >= 0; pin++) {
		pinMode(digitOutputPins[pin], OUTPUT);
		digitalWrite(digitOutputPins[pin], LOW); // Initialize to LOW
	}
}

struct OutputState {
	int state[6];
};

OutputState outputStates[] = {
	// AH, AL, BH, BL, CH, CL
	{0,0,0,0,0,0},
	{1,0,0,1,0,0},
	{1,0,0,0,0,1},
	{0,0,1,0,0,1},
	{0,1,1,0,0,0},
	{0,1,0,0,1,0},
	{0,0,0,1,1,0},
	{0,0,0,0,0,0}
};

void loopDigitalOutput(int deltaMS) {
	static uint32_t lastTS = 0;
	static int state = 0;
	uint32_t nowTS = millis();
	if (nowTS - lastTS > deltaMS) {
		lastTS += deltaMS;
		OutputState currentState = outputStates[state + 1];
		for (int pin = 0; pin < 6; pin++) {
			int port = digitOutputPins[pin];
			digitalWrite(port, (currentState.state[pin] == 1) ? HIGH : LOW);
		}
		state = (state + 1) % 6; // Cycle through 8 states
	}
}

