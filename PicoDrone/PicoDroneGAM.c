//PicoDroneGAM.c
#include "PicoDroneGAM.h"

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
    float temperature;
    float pressure;
    bool ok;
} GAM_Data;

GAM_Data gam;

void PicoDroneGAM_init()
{
    Wire.setSDA(20);
    Wire.setSCL(21);
    Wire.begin();

    gam.ok = bmp.begin(0x76);
}

void PicoDroneGAM_update()
{
    // TODO: Replace with real MPU6500 read
    gam.ax = random(-100, 100) / 100.0;
    gam.ay = random(-100, 100) / 100.0;
    gam.az = random(-100, 100) / 100.0;

    gam.gx = random(-100, 100);
    gam.gy = random(-100, 100);
    gam.gz = random(-100, 100);

    if (gam.ok)
    {
        gam.temperature = bmp.readTemperature();
        gam.pressure = bmp.readPressure();
    }
}
