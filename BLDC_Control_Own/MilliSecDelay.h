// MilliSecDelay.h

#include <Arduino.h>

class MilliSecDelay {
	uint32_t lastTS;
	uint32_t delayMS;
public:
	MilliSecDelay() : lastTS(0), delayMS(1000)
	{}
	bool TestAndSet(bool addDelta = false);
	void Restart(uint32_t ms);
};