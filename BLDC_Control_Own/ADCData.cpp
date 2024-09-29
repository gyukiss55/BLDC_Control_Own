// ADCData.cpp

#include <Arduino.h>

#include "ADCData.h"
#include "MilliSecDelay.h"
#include "ESCControl.h"

#define ADCDataSIZE 10000
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

#define _DEBUG_ADCLOOP_

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
	adcDataIndex++;
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
	uint32_t ts = 0;
	for (int i = 0; i < adcDataIndex; ++i) {
		Serial.print(i); Serial.print(". ");
		if (ts > 0) {
			Serial.print(adcDataArray[i].ts - ts); Serial.print("/");
		}
		ts = adcDataArray[i].ts;
		Serial.print(adcDataArray[i].ts); Serial.print(" # ");
		Serial.print(adcDataArray[i].analA); Serial.print(", ");
		Serial.print(adcDataArray[i].analB); Serial.print(", ");
		Serial.print(adcDataArray[i].analC); Serial.print(", ");
		Serial.println(adcDataArray[i].analD);
	}
}

void WritePulseBegin()
{
	ClearAllEscPin();
	int stat = numPulseCurrent % 6;
	switch (stat) {
	case 0:
		SetEscPinAB();
		break;
	case 1:
		SetEscPinAC();
		break;
	case 2:
		SetEscPinBC();
		break;
	case 3:
		SetEscPinBA();
		break;
	case 4:
		SetEscPinCA();
		break;
	case 5:
		SetEscPinCB();
		break;
	}
}


void WritePulseEnd()
{
	ClearAllEscPin();
}

void printDeltaUS()
{
	static uint32_t lastTs = 0;
	uint32_t cTs = micros();
	Serial.print("<");
	Serial.print(cTs);
	if (lastTs > 0 && cTs > lastTs) {
		Serial.print("-");
		Serial.print(cTs- lastTs);
	}
	Serial.print(">");
	lastTs = cTs;
}

void ExexcuteInOne()
{
	for (int ip = 0; ip < numPulse; ip++) {
		periodTimerUS.Restart(periodUS);
		pulseTimerUS.Restart(pulseUS);
		while (!pulseTimerUS.TestAndSet()) {

		}
		pulseTimerUS.Stop();
		for (sampleNr = 0; sampleNr < samplePerPeriod; sampleNr++) {
			if (sampleNr < samplePerPeriod && adcDataIndex < ADCDataSIZE - 2) {
				ADCSample();
			}
		}
		while (!periodTimerUS.TestAndSet()) {

		}
	}

	pulseTimerUS.Stop();

	DumpResult();

	status = Idle;
}


void loopADC()
{
	switch (status) {
	case Idle:
		break;
	case StartPulseBegin:
		ExexcuteInOne();
		periodTimerUS.Restart(periodUS);
		pulseTimerUS.Restart(pulseUS);
		status = StartPulseEnd;
		WritePulseBegin();

#if defined (_DEBUG_ADCLOOP_)
		printDeltaUS();
		Serial.println("StartPulseEnd");
#endif

		break;
	case StartPulseEnd:
		if (pulseTimerUS.TestAndSet()) {
			pulseTimerUS.Stop();
			WritePulseEnd();

			status = ADCSampleBegin;
			sampleNr = 0;

#if defined (_DEBUG_ADCLOOP_)
			printDeltaUS();
			Serial.println("ADCSampleBegin");
#endif
		}
		break;
	case ADCSampleBegin:
		for (int i = 0; i < samplePerPeriod; i++) {
			if (sampleNr < samplePerPeriod && adcDataIndex < ADCDataSIZE - 2) {
				ADCSample();
				sampleNr++;
			}
			else
				break;
		}
		if (sampleNr < samplePerPeriod && adcDataIndex < ADCDataSIZE - 2) {
			ADCSample();
			sampleNr++;
		}
		else {
			status = ADCSampleEnd;
			numPulseCurrent++;

#if defined (_DEBUG_ADCLOOP_)
			printDeltaUS();
			Serial.print(",");
			Serial.print(numPulseCurrent);
			Serial.println("ADCSampleEnd");
#endif

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

#if defined (_DEBUG_ADCLOOP_)
			printDeltaUS();
			Serial.print(",");
			Serial.print(numPulseCurrent);
			Serial.println("StartPulseBegin");
#endif
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
#if defined (_DEBUG_ADCLOOP_)
	printDeltaUS();
	Serial.println("SetPeriodPulseNumber");
#endif
}