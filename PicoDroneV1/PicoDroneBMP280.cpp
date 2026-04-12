//PicoDroneGAM.c

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include "PicoDroneBMP280.h"
#include "DroneData.h"


#define BMP280_ADDR 0x76

Adafruit_BMP280* bmp = nullptr; //Adafruit_BMP280(BMP280_ADDR);

void setupBMP280()
{
	bmp = new Adafruit_BMP280(&Wire);
    gam.ok = bmp->begin(BMP280_ADDR);
    Serial.print("BMP280 init start:");
    Serial.print(gam.ok);
    if (!gam.ok) {
        Serial.println("Could not find BMP280 sensor!");
        //while (1);
    } else
        Serial.println("BMP280 initialized!");

}

void PicoDroneBMP280_init()
{
	Serial.println("BMP280 setup start");
    setupBMP280();
	Serial.print("BMP280 setup status:");
    Serial.print(gam.ok);
    if (gam.ok) {
        Serial.println("BMP280 setup done!");
    }
    else {
        Serial.println("BMP280 setup failed!");
    }
}

void updateBMP280(bool log) {
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate < 200)
        return;
    lastUpdate += 100;
    if (gam.ok)
    {
        gam.temperature2 = bmp->readTemperature();
        gam.pressure = bmp->readPressure();
        gam.altitude = bmp->readAltitude(1013.25); // sea-level pressure
    }
    if (log) {
        Serial.print("Temperature = ");
        Serial.print(gam.temperature2);
        Serial.println(" °C");
        Serial.print("Pressure = ");
        Serial.print(gam.pressure);
        Serial.println(" Pa");
        Serial.print("Approx. Altitude = ");
        Serial.print(gam.altitude);
        Serial.println(" m");
	}
}

void PicoDroneBMP280_update(bool log)
{
    updateBMP280(log);
}
