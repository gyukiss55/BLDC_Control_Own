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

MilliSecDelay periodTimer;
MilliSecDelay pulseTimer;

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

	periodTimer.Restart(periodMS);
	if (pulseMS > 0 && pulseMS < periodMS)
		pulseTimer.Restart(pulseMS);
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

void TogglePort (int port, bool& state)
{
	if (state)
		digitalWrite(port, HIGH);
	else
		digitalWrite(port, LOW);
	state = !state;
}

void loopESCControl()
{
	if (pulseMS > 0 && pulseMS < periodMS && periodTimer.TestAndSet()) {
		ClearAllEscPin();
		periodTimer.Stop();
	}
	if (periodTimer.TestAndSet()) {
		phaseAll++;
		if (phaseAll >= phaseMax) {
			phaseAll = 0;
			if (periodMS != periodMSNext &&
				pulseMS != pulseMSNext) {

				periodMS = periodMSNext;
				pulseMS = pulseMSNext;
				periodTimer.Restart(periodMS);
			}
		}

		if (pulseMS > 0 && pulseMS < periodMS) {
			pulseTimer.Restart(pulseMS);
		}

		switch (phaseAll) {
		case 0:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscAPPin, HIGH);
				digitalWrite(EscBMPin, HIGH);
			}
			break;
		case 1:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscAPPin, HIGH);
				digitalWrite(EscCMPin, HIGH);
			}
			break;
		case 2:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscBPPin, HIGH);
				digitalWrite(EscCMPin, HIGH);
			}
			break;
		case 3:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscBPPin, HIGH);
				digitalWrite(EscAMPin, HIGH);
			}
			break;
		case 4:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscCPPin, HIGH);
				digitalWrite(EscAMPin, HIGH);
			}
			break;
		case 5:
			ClearAllEscPin();
			if (pulseMS > 0) {
				digitalWrite(EscCPPin, HIGH);
				digitalWrite(EscBMPin, HIGH);
			}
			break;
		}
	}
}

void SetNextPeriodPulse(int period, int pulse)
{
	periodMSNext = period;
	pulseMSNext = pulse;
}