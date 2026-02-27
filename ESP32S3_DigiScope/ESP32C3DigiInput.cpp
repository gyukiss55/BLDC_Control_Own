// ESP32C3DigiInput.cpp
#include "ESP32C3DigiInput.h"
//#include "ESP32S3RGB.h"

#define MAX_COLOR_COMBINATION 6
int colorCombinations[MAX_COLOR_COMBINATION][3] = {
	{255, 0, 0},   // Red
	{0, 255, 0},   // Green
	{0, 0, 255},   // Blue
	{255, 255, 0}, // Yellow
	{255, 0, 255}, // Magenta
	{0, 255, 255}  // Cyan
};

//int digitInputPins[6] = { 23, 22, 21, 20, 25, 33 }; // Example GPIO pins for digital input
int digitInputPins[6] = { 13, 12, 11, 10, 10, 10 }; // Example GPIO pins for digital input
bool inputStates[6] = { 0 }; // Store the state of each input pin
bool inputStatesLast[6] = { 0 }; // Store the state of each input pin
uint32_t lastInputChangeTS = 0;

void setupESP32C3DigiInput()
{
	// Configure GPIOs for digital input (example: GPIO0-GPIO7)
	for (int pin = 0;  pin < 6; pin++) {
		pinMode(digitInputPins[pin], INPUT);
	}
}


void readDigitalInput(int num)
{
	// Read digital inputs and print their states
	String str = "";
	static int count = 0;
	for (int pin = 0;  digitInputPins[pin] >= 0 && pin < num; pin++) {
		inputStates[pin] = digitalRead(digitInputPins[pin]);
		str += String(inputStates[pin]);
		str += ',';
	}
	bool changed = false;
	for (int i = 0; i < num; i++) {
		if (inputStates[i] != inputStatesLast[i]) {
			changed = true;
			inputStatesLast[i] = inputStates[i];
			//setRGB(inputStates[0] ? 255 : 0, inputStates[1] ? 255 : 0, inputStates[2] ? 255 : 0);
		}
	}
	//str += changed ? String("1") : String("0");
	//Serial.println(str);
	if (changed)
	{
		lastInputChangeTS = millis();
		//setRGBBrigthness(1);
		count++;
		int r = colorCombinations[count % MAX_COLOR_COMBINATION][0];
		int g = colorCombinations[count % MAX_COLOR_COMBINATION][1];
		int b = colorCombinations[count % MAX_COLOR_COMBINATION][2];
		//setRGB(r, g, b);
	}
	else if (millis() - lastInputChangeTS > 5000)
	{
		//setRGBBrigthness(0);
	}
}

void loopDigitalInput(int deltaMS)
{
	static uint32_t lastTS = 0;
	uint32_t nowTS = millis();
	if (nowTS - lastTS > deltaMS) {
		lastTS += deltaMS;
		readDigitalInput(3);
	}
}
