
#include <Arduino.h>
#include "Pico2W_UDPserver.h"
#include "WireCustom.h"
#include "UART9600.h"

void setup() {
	Serial.begin(115200);
	delay(2000); // Wait for serial to initialize
	setupUART9600();
	setupWire();
	setupUDPClient();
}

void loop() {
	unsigned long lastTime = 0;
	loopUART9600();
	loopUDPClient((unsigned int)8888);
	String lastMsg;
	unsigned long curr = getLastUART2Msg(lastMsg);
	if (curr > lastTime) {
		lastTime = curr;
		sendUDPMessage(lastMsg);
		Serial.print("Sent UDP message: ");
		Serial.println(lastMsg);
	}
}

