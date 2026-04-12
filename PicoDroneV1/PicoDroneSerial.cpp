//PicoDroneSerial.cpp

#include <Arduino.h>

#include "PicoDroneSerial.h"
#include "PicoDronePWM.h"
#include "PicoDroneGPS.h"
#include "DroneData.h"



void PicoDroneSerial_init()
{
    Serial.begin(115200);
}

void PicoDroneSerial_loop()
{
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint < 1000)
        return;
    lastPrint += 1000;

    Serial.println("---- STATUS ----");

    Serial.println("Acceleration in g (x,y,z):");
    Serial.print(gam.ax);
    Serial.print("   ");
    Serial.print(gam.ay);
    Serial.print("   ");
    Serial.println(gam.az);
    //Serial.print("Resultant g: ");
    //Serial.println(resultantG);

    Serial.println("Gyroscope data in degrees/s: ");
    Serial.print(gam.gx);
    Serial.print("   ");
    Serial.print(gam.gy);
    Serial.print("   ");
    Serial.println(gam.gz);

    Serial.printf("TEMP1: %.2f\n", gam.temperature1);
    Serial.printf("TEMP2: %.2f\n", gam.temperature2);
    Serial.printf("PRESS: %.2f\n", gam.pressure);
    Serial.printf("ALTIT: %.2f\n", gam.altitude);

    Serial.printf("GPS: %.5f %.5f SAT:%d\n",
        gps.lat, gps.lon, gps.sats);
	for (int i = 0; i < 4; i++)
        Serial.printf("PWM%d: %d\n", i, PicoDronePWM_get(i));
}