// BMP280_PressureSensor.h

#include <Arduino.h>

void setupBMP280PressureSensor();

void loopBMP280PressureSensor();

float readBMP280Pressure();

float readBMP280Altitude();

void jsonDumpBMP280PressureSensor(String& jsonDump);
