// PicoDroneWire.cpp

#include <Arduino.h>
#include <Wire.h>

#include "PicoDroneWire.h"

void PicoDroneWire_init() {
	Wire.setSDA(20);
	Wire.setSCL(21);
	Wire.begin();
}