// PicoDroneGPS.c

#include <Arduino.h>
#include "PicoDroneGPS.h"
#include "DroneData.h"

unsigned long lastUpdate = 0;

void PicoDroneGPS_init()
{
    Serial1.setTX(0);
    Serial1.setRX(1);
    Serial1.begin(9600);
}

void PicoDroneGPS_update()
{
    if (millis() - lastUpdate < 2000) return;
    while (Serial1.available())
    {
        String line = Serial1.readStringUntil('\n');

        if (line.startsWith("$GPGGA"))
        {
            gps.fix = true;
            gps.sats = 5; // TODO parse real value
            gps.lat = 47.0;
            gps.lon = 19.0;
        }
    }
}

float getGPSLatitude()
{
    return gps.lat;
}
float getGPSLongitude()
{
    return gps.lon;
}
int getGPSSatellites()
{
    return gps.sats;
}
