// BLDCExtInt.cpp
#include "BLDCExtInt.h"
#include "BLDCData.h"
#include "BLDCPort.h"

void ExtInterruptHandler() {
	uint32_t ts = micros();
	uint16_t inp = GPIOA->IDR & 0x07;  // PA0,PA1,PA2 bits 0,1,2
	vol_ei_ts[vol_ei_ix] = ts;
	vol_ei_inp[vol_ei_ix] = inp;
	vol_ei_ix = (vol_ei_ix + 1) % BUFFER_SIZE;
	numExtIntChangeBLDC++;
}

void setupBLDCExtInt()
{
	// External interrupts PA0,PA1,PA2 both directions (CHANGE) [web:20]
	pinMode(PA0, INPUT);
	pinMode(PA1, INPUT);
	pinMode(PA2, INPUT);
	attachInterrupt(PA0, ExtInterruptHandler, CHANGE);
	attachInterrupt(PA1, ExtInterruptHandler, CHANGE);
	attachInterrupt(PA2, ExtInterruptHandler, CHANGE);
}
