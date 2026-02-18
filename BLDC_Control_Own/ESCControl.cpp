// ESCControl.cpp

#include <Arduino.h>

#include "ESCControl.h"
#include "MilliSecDelay.h"

#define DeltaTime 20

const int EscAPPin = PB12;
const int EscAMPin = PB13;
const int EscBPPin = PB14;
const int EscBMPin = PB15;
const int EscCPPin = PB8;
const int EscCMPin = PB9;

uint8_t phaseAll = 0;
const uint8_t phaseMax = 6;

bool stateA = false;
bool stateB = false;
bool stateC = false;

int periodMS = 1000;
int pulseMS = 0;
int periodMSNext = 1000;
int pulseMSNext = 0;

//int periodUS = 20000;
//int pulseUS = 2000;
//int numPulse = 4;

MilliSecDelay periodTimerMS;
MilliSecDelay pulseTimerMS;

void ClearAllEscPin();

void setupESCControl()
{
	pinMode(EscAPPin, OUTPUT);
	pinMode(EscAMPin, OUTPUT);
	pinMode(EscBPPin, OUTPUT);
	pinMode(EscBMPin, OUTPUT);
	pinMode(EscCPPin, OUTPUT);
	pinMode(EscCMPin, OUTPUT);

	ClearAllEscPin();

	periodTimerMS.Restart(periodMS);
	if (pulseMS > 0 && pulseMS < periodMS)
		pulseTimerMS.Restart(pulseMS);
}

void ClearAllEscPin()
{
	digitalWrite(EscAPPin, LOW);
	digitalWrite(EscBPPin, LOW);
	digitalWrite(EscCPPin, LOW);
	digitalWrite(EscAMPin, LOW);
	digitalWrite(EscBMPin, LOW);
	digitalWrite(EscCMPin, LOW);
}

void SetEscPinAB()
{
	digitalWrite(EscAPPin, HIGH);
	digitalWrite(EscBMPin, HIGH);
}

void SetEscPinAC()
{
	digitalWrite(EscAPPin, HIGH);
	digitalWrite(EscCMPin, HIGH);
}

void SetEscPinBC()
{
	digitalWrite(EscBPPin, HIGH);
	digitalWrite(EscCMPin, HIGH);
}

void SetEscPinBA()
{
	digitalWrite(EscBPPin, HIGH);
	digitalWrite(EscAMPin, HIGH);
}

void SetEscPinCA()
{
	digitalWrite(EscCPPin, HIGH);
	digitalWrite(EscAMPin, HIGH);
}

void SetEscPinCB()
{
	digitalWrite(EscCPPin, HIGH);
	digitalWrite(EscBMPin, HIGH);
}

void TogglePort (int port, bool& state)
{
	if (state)
		digitalWrite(port, HIGH);
	else
		digitalWrite(port, LOW);
	state = !state;
}

void DumpPhase ()
{
    Serial.print (millis ());
    Serial.print ("-t1:");
    Serial.print (periodMS);
    Serial.print (",t2:");
    Serial.print (pulseMS);
    Serial.print (",A+");
    Serial.print (digitalRead(EscAPPin));
    Serial.print (",A-");
    Serial.print (digitalRead(EscAMPin));
    Serial.print (",B+");
    Serial.print (digitalRead(EscBPPin));
    Serial.print (",B-");
    Serial.print (digitalRead(EscBMPin));
    Serial.print (",C+");
    Serial.print (digitalRead(EscCPPin));
    Serial.print (",C-");
    Serial.println (digitalRead(EscCMPin));

}

void loopESCControl()
{
	if (pulseMS > 0 && pulseMS < periodMS && pulseTimerMS.TestAndSet()) {
		ClearAllEscPin();
		pulseTimerMS.Stop();
		DumpPhase ();
	}
	if (periodTimerMS.TestAndSet()) {
		phaseAll++;
		if (phaseAll >= phaseMax) {
			phaseAll = 0;
			if (periodMS != periodMSNext ||
				pulseMS != pulseMSNext) {

				periodMS = periodMSNext;
				pulseMS = pulseMSNext;
				periodTimerMS.Restart(periodMS);
			}
		}

		if (pulseMS > 0 && pulseMS < periodMS) {
			pulseTimerMS.Restart(pulseMS);
		}

    

		switch (phaseAll) {
		case 0:
			ClearAllEscPin();
			if (pulseMS > 0) 
				SetEscPinAB();
			break;
		case 1:
			ClearAllEscPin();
			if (pulseMS > 0)
				SetEscPinAC();
			break;
		case 2:
			ClearAllEscPin();
			if (pulseMS > 0) 
				SetEscPinBC();
			break;
		case 3:
			ClearAllEscPin();
			if (pulseMS > 0) 
				SetEscPinBA();
			break;
		case 4:
			ClearAllEscPin();
			if (pulseMS > 0) 
				SetEscPinCA();
			break;
		case 5:
			ClearAllEscPin();
			if (pulseMS > 0) 
				SetEscPinCB();
			break;
		}
		DumpPhase ();
	}
}

void SetNextPeriodPulse(int period, int pulse)
{
	periodMSNext = period;
	pulseMSNext = pulse;
}

int GetNextPeriod()
{
	return periodMSNext;
}
int GetNextPulse()
{
	return pulseMSNext;
}


