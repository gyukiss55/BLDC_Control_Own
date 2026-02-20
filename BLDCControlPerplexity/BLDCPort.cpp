// BLDCPort.cpp
#include "BLDCPort.h"


void setupBLDCPort()
{
	pinMode(LED_BUILTIN, OUTPUT);

	// BLDC outputs PB12-PB15,PB8,PB9 [web:1]
	pinMode(PB12, OUTPUT);
	pinMode(PB13, OUTPUT);
	pinMode(PB14, OUTPUT);
	pinMode(PB15, OUTPUT);
	pinMode(PB8, OUTPUT);
	pinMode(PB9, OUTPUT);
}