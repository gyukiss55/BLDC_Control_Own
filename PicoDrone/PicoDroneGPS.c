// PicoDroneGPS.c
#include "PicoDroneGPS.h"

#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial GPS(0);

typedef struct {
    float lat;
    float lon;
    int sats;
    bool fix;
} GPS_Data;

GPS_Data gps;

unsigned long lastUpdate = 0;

void PicoDroneGPS_init()
{
    GPS.setTX(0);
    GPS.setRX(1);
    GPS.begin(9600);
}

void PicoDroneGPS_update()
{
    if (millis() - lastUpdate < 2000) return;
    while (GPS.available())
    {
        String line = GPS.readStringUntil('\n');

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
