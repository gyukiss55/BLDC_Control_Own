// MilliSecDelay.cpp

#include <Arduino.h>
#include "MilliSecDelay.h"

bool MilliSecDelay::TestAndSet(bool addDelta)
{
	uint32_t ts = millis();
	if (ts - lastTS > delayMS) {
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
}
