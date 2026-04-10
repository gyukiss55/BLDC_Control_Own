//PicoDroneSerial.c

#include <Arduino.h>

#include "PicoDroneSerial.h"
#include "PicoDronePWM.h"
#include "PicoDroneGAM.h"
#include "PicoDroneGPS.h"


unsigned long lastPrint = 0;

void PicoDroneSerial_init()
{
    //Serial.begin(115200);
}

void PicoDroneSerial_loop()
{
    if (millis() - lastPrint < 1000) return;
    lastPrint = millis();

    Serial.println("---- STATUS ----");

    Serial.printf("TEMP: %.2f\n", gam.temperature);
    Serial.printf("PRESS: %.2f\n", gam.pressure);

    Serial.printf("GPS: %.5f %.5f SAT:%d\n",
        gps.lat, gps.lon, gps.sats);

    for (int i = 0; i < 4; i++)
        Serial.printf("PWM%d: %d\n", i, PicoDronePWM_get(i));
}