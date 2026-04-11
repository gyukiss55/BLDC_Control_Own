#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280* bmp = NULL; // I2C

void setupPicoBMP280() {
    while (!Serial);

    Wire.setSDA(20);
    Wire.setSCL(21);
    Wire.begin();
    Serial.println("BMP280 test");

    bmp = new Adafruit_BMP280(&Wire);

    // Try address 0x76 or 0x77
    if (!bmp->begin(0x76)) {
        Serial.println("Could not find BMP280 sensor!");
        while (1);
    }

    Serial.println("BMP280 initialized!");
}

void loopPicoBMP280() {
    Serial.print("Temperature = ");
    Serial.print(bmp->readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");
    Serial.print(bmp->readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx Altitude = ");
    Serial.print(bmp->readAltitude(1013.25)); // sea-level pressure
    Serial.println(" m");

    Serial.println();
    delay(2000);
}