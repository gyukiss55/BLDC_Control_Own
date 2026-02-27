// BLDCSerial.cpp - BLDCSerial class implementation for ESP32 Lilo BLDC Control

#include "BLDCSerial.h"
#include "BLDCPort.h"

void setupSerial()
{
	Serial.begin(115200);
	delay(2000);
	Serial.println("ESP32 Lilo BLDC Control start...");
	delay(1000);
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
			int period = str1.toInt();
			int duty = str2.toInt();
			setBLDCPeriod(period);
			setBLDCPWM(duty);
			Serial.printf("Set Period:%d, Pulse:%d\n", period, duty);
			//Serial.println(vol_m_control);
		}
	}
}
