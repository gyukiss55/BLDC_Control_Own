// CommonData.cpp

#include <Arduino.h>

#include "CommonData.h"


volatile int hallCounter = 0;
volatile int hallCounterPerMin = 0;

int speed = 6553;   // 10% duty (ESC min)
int speed1 = 6553;

