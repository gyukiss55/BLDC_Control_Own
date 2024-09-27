// ADCData.h

#include <Arduino.h>

struct ADCData {
	uint32_t ts;
	uint16_t analA;
	uint16_t analB;
	uint16_t analC;
	uint16_t analD;
};

void setupADC();
void loopADC();
void SetPeriodPulseNumber(int period, int pulse, int number);
