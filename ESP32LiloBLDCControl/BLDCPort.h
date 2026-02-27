#ifndef BLDC_PORT_H
#define BLDC_PORT_H

#include <Arduino.h>

void setupBLDCPort();
int setBLDCPeriod(int usec);
int setBLDCPWM(int duty);
void loopBLDCPort();

#endif