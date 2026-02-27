// BLDCPort.cpp
#include "BLDCPort.h"

void clearBLDCPort();

void setupBLDCPort()
{
	pinMode(LED_BUILTIN, OUTPUT);

	// BLDC outputs PB12-PB15,PB8,PB9 [web:1]
	pinMode(BLDC_PINAH, OUTPUT);
	pinMode(BLDC_PINAL, OUTPUT);
	pinMode(BLDC_PINBH, OUTPUT);
	pinMode(BLDC_PINBL, OUTPUT);
	pinMode(BLDC_PINCH, OUTPUT);
	pinMode(BLDC_PINCL, OUTPUT);

	pinMode(BLDC_PINTT, OUTPUT);
	digitalWrite(BLDC_PINTT, LOW);

	clearBLDCPort();
}

void clearBLDCPort()
{
	digitalWrite(BLDC_PINAH, LOW);
	digitalWrite(BLDC_PINAL, LOW);
	digitalWrite(BLDC_PINBH, LOW);
	digitalWrite(BLDC_PINBL, LOW);
	digitalWrite(BLDC_PINCH, LOW);
	digitalWrite(BLDC_PINCL, LOW);
}

void unitTestBLDCPort()
{
	clearBLDCPort();
	delay(100);

	digitalWrite(BLDC_PINAH, HIGH);
	delay(100);
	digitalWrite(BLDC_PINAH, LOW);
	digitalWrite(BLDC_PINAL, HIGH);
	delay(100);
	digitalWrite(BLDC_PINAL, LOW);
	digitalWrite(BLDC_PINBH, HIGH);
	delay(100);
	digitalWrite(BLDC_PINBH, LOW);
	digitalWrite(BLDC_PINBL, HIGH);
	delay(100);
	digitalWrite(BLDC_PINBL, LOW);
	digitalWrite(BLDC_PINCH, HIGH);
	delay(100);
	digitalWrite(BLDC_PINCH, LOW);
	digitalWrite(BLDC_PINCL, HIGH);
	delay(100);
	digitalWrite(BLDC_PINCL, LOW);

}
