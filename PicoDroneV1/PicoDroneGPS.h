// PicoDroneGPS.h
#ifndef PICODRONEGPS_H
#define PICODRONEGPS_H

#include <Arduino.h>

void PicoDroneGPS_init();
void PicoDroneGPS_update();
float getGPSLatitude();
float getGPSLongitude();
int getGPSSatellites();

#endif // !PICODRONEGPS_H