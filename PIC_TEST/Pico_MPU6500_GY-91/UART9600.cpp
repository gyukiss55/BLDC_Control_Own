//UART9600.cpp
#include <Arduino.h>
#include "UART9600.h"



String lastMsg;
unsigned long lastTS = 0;

void testUART9600() {
	if (Serial2.available()) {
		String receivedData = Serial2.readStringUntil('\n');
		Serial.print("Received from UART9600: ");
		Serial.println(receivedData);
	}
	else {
		for (int i = 0; i < 80; i++) {
			Serial2.print("U");
		}
		Serial.println("U");
	}
}

void setupUART9600() {
	Serial2.setTX(8);       // GPIO8 = TX
	Serial2.setRX(9);		// GPIO9 = RX
	Serial2.begin(9600);
	//while (!Serial2) {
	//	delay(10); // Wait for Serial2 to be ready
	//}
	delay(1000);
	Serial.println("UART9600 initialized at 9600 baud rate");

	//testUART9600();
}

void loopUART9600() {
	if (Serial.available()) {
		String receivedData1 = Serial.readStringUntil('\n');
		Serial.println(receivedData1);
	}
	String receivedData2All;
	while (Serial2.available()) {
		String receivedData2 = Serial2.readStringUntil('\n');
		Serial.print(receivedData2);
		if (receivedData2.startsWith("$GPRMC") ||
			receivedData2.startsWith("$GPGGA") ||
			receivedData2.startsWith("$GPGSA") ||
			receivedData2.startsWith("$GPGSV"))
			receivedData2All += receivedData2;
	}
	if (receivedData2All.length() > 0) {
		lastTS = millis();
		lastMsg = receivedData2All;
	}
}

unsigned long getLastUART2Msg (String& str)
{
	str = String (lastTS) + "+" + lastMsg;
	return lastTS;
}
