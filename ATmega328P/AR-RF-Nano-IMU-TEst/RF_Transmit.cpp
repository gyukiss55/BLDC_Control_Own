// RF_Transmit.cpp
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "RF_Radio.h"
#include "RF_Transmit.h"

#define RF_BUFFER_SIZE 32

const byte address[6] = "00001";
char bufferTX[RF_BUFFER_SIZE];

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

void startRFTransmit(const String& message) {

    // This device is a TX node
	uint16_t messageLength = message.length();
    uint16_t transmittedLength = 0;
    uint8_t i = 0;
    {
        radio.flush_tx();
        uint8_t failures = 0;
        unsigned long start_timer = micros();  // start the timer
        while (transmittedLength < messageLength) {

			if (messageLength - transmittedLength >= RF_BUFFER_SIZE) {
				strncpy(bufferTX, message.c_str() + transmittedLength, RF_BUFFER_SIZE);
			}
			else {
				strncpy(bufferTX, message.c_str() + transmittedLength, RF_BUFFER_SIZE);
				bufferTX[messageLength - transmittedLength] = '\0'; // Null-terminate the last chunk
			}

            if (!radio.writeFast(&bufferTX, RF_BUFFER_SIZE)) {
                uint8_t flags = radio.getStatusFlags();
                if (flags & RF24_TX_DF) {
                    failures++;
                    // now we need to reset the tx_df flag and the radio's CE pin
                    radio.ce(LOW);
                    radio.clearStatusFlags(RF24_TX_DF);
                    radio.ce(HIGH);
                }
                // else the TX FIFO is full; just continue loop.
            }
            else {
                i++;
				transmittedLength += RF_BUFFER_SIZE;
            }

            if (failures >= 100) {
                Serial.print(F("Too many failures detected. Aborting at payload "));
                Serial.println(bufferTX[0]);
                break;
            }
        }
        unsigned long end_timer = micros();  // end the timer

        Serial.print(F("Time to transmit = "));
        Serial.print(end_timer - start_timer);  // print the timer result
        Serial.print(F(" us with "));
        Serial.print(failures);  // print failures detected
        Serial.println(F(" failures detected"));

    }
}

