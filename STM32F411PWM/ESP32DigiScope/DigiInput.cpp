// DigiInput.cpp


#include <Arduino.h>
#include "DigiInput.h"
#include "MilliSecDelay.h"

#define DigiInput1 19
#define DigiInput2 18
#define DigiInput3 32
#define DigiInput4 33
#define DigiInput5 34
#define DigiInput6 35

struct Sample {
	uint32_t status;
	uint32_t microsec;
};

#define SampleNr 100
uint32_t sampleIndex = 0;
Sample sampleVector[SampleNr];
Sample lastSample;


void setupDigiInput()
{
	pinMode(DigiInput1, INPUT);
	pinMode(DigiInput2, INPUT);
	pinMode(DigiInput3, INPUT);
	pinMode(DigiInput4, INPUT);
	pinMode(DigiInput5, INPUT);
	pinMode(DigiInput6, INPUT);
}

void ClearSample()
{
	Sample s;
	s.status = 0xff;
	s.microsec = 0;
	for (int i = 0; i < SampleNr; i++) {
		sampleVector[i] = s;
	}
}

void Measure()
{
	ClearSample();
	sampleIndex = 0;
	MilliSecDelay delMS;
	delMS.Restart(100);
	while (!delMS.TestAndSet() && sampleIndex < SampleNr - 1) {
		Sample& s = lastSample;
		s.microsec = micros();
		s.status = 0;
		if (digitalRead(DigiInput1) == 1)
			s.status |= 1;
		if (digitalRead(DigiInput2) == 1)
			s.status |= 2;
		if (digitalRead(DigiInput3) == 1)
			s.status |= 4;
		if (digitalRead(DigiInput4) == 1)
			s.status |= 8;
		if (digitalRead(DigiInput5) == 1)
			s.status |= 0x10;
		if (digitalRead(DigiInput6) == 1)
			s.status |= 0x20;
		if ((sampleIndex == 0) || (sampleVector[sampleIndex - 1].status != s.status)) {
			sampleVector[sampleIndex] = s;
			sampleIndex++;
		}
	}
}


void PrintStatus(Sample& s, uint32_t mask)
{
	if ((s.status & mask) == 0)
		Serial.print("L");
	else
		Serial.print("H");
}

void PrintStatus(String str, uint32_t mask)
{
	if (sampleIndex < 2)
		return;
	Sample& s1 = sampleVector[0];
	Serial.print(str);
	PrintStatus(s1, mask);
	bool first = true;
	for (int i = 1; i < sampleIndex; i++) {
		Sample& s2 = sampleVector[i];
		if ((s2.status & mask) != (s1.status & mask)) {
			if (first)
				first = false;
			else
				PrintStatus(s1, mask);
			Serial.print("[");
			Serial.print((s2.microsec - s1.microsec));
			Serial.print("],");
			s1 = s2;
		}
	}
	Serial.println("");
}

void PrintResult()
{
	if (sampleIndex == 0) {
		Serial.print(micros());
		Serial.println(" - NoResult");
	} else
	if (sampleIndex == 1) {
		Serial.print(micros());
		Serial.print(" - 1:");
		PrintStatus(sampleVector[0], 1);
		Serial.print(", 2:");
		PrintStatus(sampleVector[0], 2);
		Serial.print(", 3:");
		PrintStatus(sampleVector[0], 4);
		Serial.print(", 4:");
		PrintStatus(sampleVector[0], 8);
		Serial.print(", 5:");
		PrintStatus(sampleVector[0], 0x10);
		Serial.print(", 6:");
		PrintStatus(sampleVector[0], 0x20);
		Serial.println("");
	}
	else {
		Serial.print(micros());
		Serial.println("");
		PrintStatus("1:", 1);
		PrintStatus("2:", 2);
		PrintStatus("3:", 4);
		PrintStatus("4:", 8);
		PrintStatus("5:", 0x10);
		PrintStatus("6:", 0x20);
	}
}

void DumpResult()
{
	int j = 0;
	for (uint32_t i = 1; i < sampleIndex; ++i, ++j) {
		if (j == 0) {
			Serial.print(i);
			Serial.print(":");
		}
		Serial.print(sampleVector[i-1].status, HEX);
		Serial.print("-");
		Serial.print(sampleVector[i].status, HEX);
		Serial.print("[");
		Serial.print(sampleVector[i].microsec - sampleVector[i-1].microsec);
		Serial.print("],");
		if (j == 15) {
			Serial.println("");
			j = -1;
		}
	}
}


void loopDigiInput()
{
	MilliSecDelay delMS;
	delMS.Restart(5000);
	Measure();
	PrintResult();
	DumpResult();
	while (!delMS.TestAndSet()) {

	}
}
