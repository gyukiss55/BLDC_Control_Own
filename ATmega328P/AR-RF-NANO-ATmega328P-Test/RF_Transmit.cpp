// RF_Transmit.cpp
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_Radio.h"
#include "RF_Transmit.h"


const byte address[6] = "00001";

void setupRFTransmit() {
	radio.begin();
	radio.openWritingPipe(address);
	radio.setPALevel(RF24_PA_MIN);
	radio.stopListening();
}

void loopRFTransmit() {
	static int nbr = 1000;
	radio.write(&nbr, sizeof(nbr));
  nbr++;
	delay(1000);
}
