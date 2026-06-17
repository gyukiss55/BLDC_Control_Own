//UART9600.cpp
#include <Arduino.h>
#include "UART9600.h"

void setupUART9600() {
	Serial1.setTX(8);       // GPIO8 = TX
	Serial1.setRX(9);		// GPIO9 = RX
	Serial1.begin(9600);
	//while (!Serial1) {
	//	delay(10); // Wait for Serial1 to be ready
	//}
	delay(1000);
	Serial.println("UART9600 initialized at 9600 baud rate");
}

void loopUART9600() {
	if (Serial.available()) {
		String receivedData1 = Serial.readStringUntil('\n');
		Serial1.println(receivedData1);
	}
	if (Serial1.available()) {
		String receivedData2 = Serial1.readStringUntil('\n');
		Serial.println(receivedData2);
	}
}