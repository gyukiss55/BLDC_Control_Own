// RF_Receiver.cpp
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_Radio.h"
#include "RF_Receiver.h"


const byte address[6] = "00001";
char buffer[32+1];

void setupRFReceiver() {
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
}

bool loopRFReceiver() {
	static String receivedMessage;
    if (radio.available()) {
        buffer[sizeof(buffer) - 1] = '\0'; // Null-terminate the string
        radio.read(buffer, sizeof(buffer) - 1);

        int len = strlen(buffer);
        if (len > 0) {
			receivedMessage += buffer;
        }

        if (len < 32 || receivedMessage.length() > 200) {
            Serial.print("Rec:");
			Serial.println(receivedMessage.length());
			Serial.println(receivedMessage);
            receivedMessage = "";
        }

        return true;
    }
    return false;
}
