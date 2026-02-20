// BLDCSerial.cpp
#include "BLDCSerial.h"
#include "BLDCData.h"
#include "BLDCPort.h"

void SnapshotBLDCControl();

void setupSerial()
{
	Serial.begin(115200);
	delay(2000);
	Serial.println("STM32F411CE start...");
}

void SerialOutputLoop()
{
	static uint32_t lastTS = 0;
	uint32_t nowTS = millis();
	const uint32_t DeltaTS = 1000;
	if (nowTS - lastTS >= DeltaTS) {
		lastTS += DeltaTS;
		//Serial.printf("%d. TI:%d, EI:%d, FB:%d, Period:%d, Pulse:%d\n", nowTS, periodMS, pulseMS);
		Serial.printf("%d,%d,%d,%d,%d\n", numTimerIntChangeBLDC, numExtIntChangeBLDC, numFillBLDC, periodMS, pulseMS);
		//Serial.printf("%d,%d\n", digitalRead(PB12), digitalRead(PB8));
	}
}


void SerialInputLoop()
{
	static String serialInput = "";

	while (Serial.available()) {
		char ch = Serial.read();
		serialInput.concat(ch);
		//Serial.write(ch);
	}
	String str0;
	if (serialInput.length() > 0) {
		//Serial.print(serialInput);
		int pos = serialInput.indexOf("\n");
		if (pos > 0 && pos < serialInput.length()) {
			str0 = serialInput;
			serialInput = "";
		}
	}
	if (str0.length() > 0) {
		int pos = str0.indexOf(",");
		if (pos > 0 && pos < str0.length()) {
			String str1 = str0.substring(0, pos);
			String str2 = str0.substring(pos + 1);
			periodMS = str1.toInt();
			pulseMS = str2.toInt();
			Serial.printf("Set Period:%d, Pulse:%d, %x, %x\n", periodMS, pulseMS, BLDC_MASKAHBL, BLDC_MASKAHCL);
			//Serial.println(vol_m_control);
		}
	}
}

void SnapshotBLDCControl()
{
	for (int i = 0; i < BUFFER_SIZE; i++) {
		int j = (vol_ti_ix_rd + i) % BUFFER_SIZE;
		Serial.printf("%d:%02X ", vol_ti_ts[j], vol_ti_BLDC[j]);
	}
	Serial.println();
}
