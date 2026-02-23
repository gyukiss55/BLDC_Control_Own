// BLDCSerial.cpp
#include "BLDCSerial.h"
#include "BLDCData.h"
#include "BLDCPort.h"

void SnapshotBLDCControl();

void setupSerial()
{
	Serial.begin(115200);
	delay(2000);
	Serial.println("STM32F411CE start Ver 0.91 ...");
	Serial.printf("%x, %x, %x, %x, %x, %x,\n",
		BLDC_MASKAHBL, BLDC_MASKAHCL,
		BLDC_MASKBHCL, BLDC_MASKBHAL,
		BLDC_MASKCHAL, BLDC_MASKCHBL);
	delay(10000);
}

void SerialOutputLoop()
{
	static bool debug_flag = false;
	static uint32_t lastTS = 0;
	uint32_t nowTS = millis();
	const uint32_t DeltaTS1 = 5000;
	static int num = 0;
	if (nowTS - lastTS >= DeltaTS1) {
		lastTS += DeltaTS1;
		//Serial.printf("%d. TI:%d, EI:%d, FB:%d, Period:%d, Pulse:%d\n", nowTS, periodMS, pulseMS);
		Serial.printf("%d,%d,%d,%d,%d\n", numTimerIntChangeBLDC, numExtIntChangeBLDC, numFillBLDC, periodMS, pulseMS);
		//Serial.printf("%d,%d\n", digitalRead(PB12), digitalRead(PB8));
		num++;
		if (debug_flag && (num % 4 == 0)) {
			SnapshotBLDCControl();
		}
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
	uint32_t sn_t[BUFFER_SIZE] = { 0 };
	uint16_t sn_v[BUFFER_SIZE] = { 0 };
	int ix = vol_ti_ix_wr;

	for (int i = 0; i < BUFFER_SIZE; i++) {
		int j = (ix + i) % BUFFER_SIZE;
		sn_t[i] = vol_ti_ts[j];
		sn_v[i] = vol_ti_BLDC[j];
	}
	uint32_t t0 = sn_t[0];

	Serial.print(ix);
	Serial.print(":");
	Serial.print(t0);
	Serial.print("-");
	for (int i = 0; i < BUFFER_SIZE; i++) {
		int j = (ix + i) % BUFFER_SIZE;
		Serial.printf(" %d,",j);
		Serial.printf("%d,", (sn_t[i] - t0));
		Serial.printf("%04X;", sn_v[i]);
	}
}
