// RF_Receiver.cpp
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_Radio.h"
#include "RF_Receiver.h"


const byte address[6] = "00001";

char bufferRX[256];

void setupRFReceiver() {
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
}

bool loopRFReceiver() {
    if (radio.available()) {
        int nbr = 0;
        Serial.print(" - received:");
        bufferRX[sizeof(bufferRX) - 1] = '\0'; // Null-terminate the string
        radio.read(bufferRX, sizeof(bufferRX) - 1);
		int len = strlen(bufferRX);
        Serial.print(millis());
		Serial.print(" - received:");
		Serial.print(len);
        Serial.print(" data:");
        Serial.println(bufferRX);
        return true;
    }
    return false;
}
