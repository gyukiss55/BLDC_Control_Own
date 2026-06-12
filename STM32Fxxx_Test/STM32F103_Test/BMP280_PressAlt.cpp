// BMP280_PressAlt.cpp

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


// Create instances for the sensors
Adafruit_BMP280 bmp; // BMP280 instance


void setupBMP280() {

    // Initialize BMP280
    if (!bmp.begin(0x76)) { // Default I2C address for BMP280 is 0x76
        Serial.println("BMP280 initialization failed!");
        while (1);
    }
    Serial.println("BMP280 initialized successfully.");


}

void loopBMP280(int delayMS) {
    // Read BMP280 data
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude(1013.25); // Sea level pressure in hPa


    // Print sensor data
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" Pa");
    Serial.print("Altitude: "); Serial.print(altitude); Serial.println(" m");

    delay(delayMS); // Wait 1 second before the next reading
}

void dumpBMP280(String& message) {
    // Read BMP280 data
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude(1013.25); // Sea level pressure in hPa
	message = "Temp:" + String(temperature) + ", Press:" + String(pressure, 0) + ", Alt:" + String(altitude, 0);
}
