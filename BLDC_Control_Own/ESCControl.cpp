// ESCControl.cpp

#include <Arduino.h>

#include "ESCControl.h"
#include "MilliSecDelay.h"

#define DeltaTime 20

const int EscAPin = PB12;
const int EscBPin = PB13;
const int EscCPin = PB14;

uint8_t phaseAll = 0;

bool stateA = false;
bool stateB = false;
bool stateC = false;

MilliSecDelay timerAll;

void setupESCControl()
{
	pinMode(EscAPin, OUTPUT);
	pinMode(EscBPin, OUTPUT);
	pinMode(EscCPin, OUTPUT);
	digitalWrite(EscAPin, LOW);
	digitalWrite(EscBPin, LOW);
	digitalWrite(EscCPin, LOW);

	timerAll.Restart(DeltaTime);
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
	if (timerAll.TestAndSet()) {
		phaseAll++;
		if (phaseAll > 3)
			phaseAll = 0;
	}
	switch (phaseAll) {
	case 0:
		TogglePort(EscAPin, stateA);
		TogglePort(EscBPin, stateB);
		stateC = false;
		digitalWrite(EscCPin, LOW);
		break;
	case 1:
		TogglePort(EscBPin, stateB);
		TogglePort(EscCPin, stateC);
		stateA = false;
		digitalWrite(EscAPin, LOW);
		break;
	case 2:
		TogglePort(EscAPin, stateA);
		TogglePort(EscCPin, stateC);
		stateB = false;
		digitalWrite(EscBPin, LOW);
		break;
	}
}