// ADCData.cpp

#include <Arduino.h>

#include "ADCData.h"
#include "MilliSecDelay.h"

#define ADCDataSIZE 600
ADCData adcDataArray[ADCDataSIZE];
uint32_t adcDataIndex = 0;

#if defined(STM32F1xx)

#define ADCA PA1
#define ADCB PA2
#define ADCC PA3
#define ADCD PA4

#elif defined(STM32F4xx)

#define ADCA PA0
#define ADCB PA1
#define ADCC PA2
#define ADCD PA3

#else
assert defined !!!!RASPI not defined
 
#endif

enum ADCStatusEnum {
	Idle = 0,
	StartPulseBegin,
	StartPulseEnd,
	ADCSampleBegin,
	ADCSampleEnd,
	NoMore
};

int periodUS = 20000;
int pulseUS = 2000;
int numPulse = 4;
int numPulseCurrent = 0;
int sampleNr = 0;
const int samplePerPeriod = 200;
ADCStatusEnum status = Idle;

MicroSecDelay periodTimerUS;
MicroSecDelay pulseTimerUS;



uint32_t ADCSample()
{
	adcDataArray[adcDataIndex].ts = micros();
	adcDataArray[adcDataIndex].analA = analogRead(ADCA);
	adcDataArray[adcDataIndex].analB = analogRead(ADCB);
	adcDataArray[adcDataIndex].analC = analogRead(ADCC);
	adcDataArray[adcDataIndex].analD = analogRead(ADCD);
	adcDataIndex;
	if (adcDataIndex == ADCDataSIZE) {
		adcDataIndex = 0;
	}
	return adcDataIndex;
}

void setupADC()
{
	pinMode(ADCA, INPUT_ANALOG);
	pinMode(ADCB, INPUT_ANALOG);
	pinMode(ADCC, INPUT_ANALOG);
	pinMode(ADCD, INPUT_ANALOG);
}

void DumpResult()
{
	Serial.print("index:"); Serial.println(adcDataIndex);
	for (int i = 0; i < adcDataIndex; ++i) {
		Serial.print(i); Serial.print(". ");
		Serial.print(adcDataArray[i].ts); Serial.print("- ");
		Serial.print(adcDataArray[i].analA); Serial.print(", ");
		Serial.print(adcDataArray[i].analB); Serial.print(", ");
		Serial.print(adcDataArray[i].analC); Serial.print(", ");
		Serial.println(adcDataArray[i].analD);
	}
}

void loopADC()
{
	switch (status) {
	case Idle:
		break;
	case StartPulseBegin:
		periodTimerUS.Restart(periodUS);
		pulseTimerUS.Restart(pulseUS);
		status = StartPulseEnd;
		break;
	case StartPulseEnd:
		if (pulseTimerUS.TestAndSet()) {
			pulseTimerUS.Stop();
			status = ADCSampleBegin;
			sampleNr = 0;
		}
		break;
	case ADCSampleBegin:
		if (sampleNr < samplePerPeriod && adcDataIndex < ADCDataSIZE - 2) {
			ADCSample();
		}
		else {
			status = ADCSampleEnd;
			numPulseCurrent++;
			if (numPulseCurrent >= numPulse) {
				periodTimerUS.Stop();
				pulseTimerUS.Stop();

				DumpResult();

				status = Idle;
			}
		}
		break;
	case ADCSampleEnd:
		if (periodTimerUS.TestAndSet()) {
			status = StartPulseBegin;
		}
		break;
	case NoMore:
		break;
	}
}

void SetPeriodPulseNumber(int period, int pulse, int number)
{
	periodUS = period;
	pulseUS = pulse;
	numPulse = number;
	status = StartPulseBegin;
	adcDataIndex = 0;
	numPulseCurrent = 0;
}