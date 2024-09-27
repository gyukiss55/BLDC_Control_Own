// MilliSecDelay.cpp

#include <Arduino.h>
#include "MilliSecDelay.h"

bool MilliSecDelay::TestAndSet(bool addDelta)
{
	uint32_t ts = millis();
	if (run && (ts - lastTS) > delayMS) {
		if (addDelta)
			lastTS = lastTS + delayMS;
		else
			lastTS = ts;
		return true;
	}
	return false;
}

void MilliSecDelay::Restart(uint32_t ms)
{
	delayMS = ms;
	lastTS = millis ();
	run = true;
}

bool MicroSecDelay::TestAndSet(bool addDelta)
{
	uint32_t ts = micros();
	if (run && (ts - lastTS) > delayUS) {
		if (addDelta)
			lastTS = lastTS + delayUS;
		else
			lastTS = ts;
		return true;
	}
	return false;
}

void MicroSecDelay::Restart(uint32_t us)
{
	delayUS = us;
	lastTS = micros();
	run = true;
}

