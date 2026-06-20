// BMP280_PressureSensor.cpp

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "jsonDump.h"

static Adafruit_BMP280* bmpPtr = nullptr;

void setupBMP280PressureSensor() {
	// BMP280 init
	bmpPtr = new Adafruit_BMP280();
	if (!bmpPtr->begin(0x76)) {
		Serial.println("BMP280 not found!");
		while (1);
	}

	Serial.println("BMP280 initialized");

	delay(1000);
}

float readBMP280Pressure() {
	return bmpPtr->readPressure() / 100.0; // hPa
}

float readBMP280Altitude() {
	return bmpPtr->readAltitude(1013.25);
}

void loopBMP280PressureSensor() {

	float pressure = bmpPtr->readPressure() / 100.0; // hPa
	float altitude = bmpPtr->readAltitude(1013.25);

	Serial.println("==============");

	// Pressure
	Serial.print("Pressure: ");
	Serial.print(pressure);
	Serial.println(" hPa");

	// Altitude
	Serial.print("Altitude: ");
	Serial.print(altitude);
	Serial.println(" m");

}

void jsonDumpBMP280PressureSensor(String& jsonStr) {
	float pressure = bmpPtr->readPressure() / 100.0; // hPa
	float altitude = bmpPtr->readAltitude(1013.25);
	jsonDump("Pre", pressure, jsonStr);
	jsonDump("Alt", altitude, jsonStr);
}
