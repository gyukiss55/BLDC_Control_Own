// NRF24L01 don't reuse D9,10,11,12,13 pins!
// 9-CSN
// 10-CE
// 11-MOSI
// 12-MISO
// 13-SCK

//#define _RF_Transmit_mode_
#define _RF_Receiver_mode_

#include <Arduino.h>
#if defined(_RF_Transmit_mode_)
#include "RF_Transmit.h"
#elif defined(_RF_Receiver_mode_)
#include "RF_Receiver.h"
#endif



void setup()
{
    Serial.begin(115200);

    // Wait for Serial (USB CDC )
    delay(1000);
    Serial.println("Hello World!");

    #if defined(_RF_Transmit_mode_)

    setupRFTransmit();
    Serial.println("RF Transmit Mode");

    #elif defined(_RF_Receiver_mode_)

    setupRFReceiver();
    Serial.println("RF Receiver Mode");

    #endif

}

void loop()
{
    static uint32_t counter = 0;

    //Serial.print("Hello World! Count = ");
    //Serial.println(counter++);
    Serial.print(".");

    #if defined(_RF_Transmit_mode_)

    loopRFTransmit();

    #elif defined(_RF_Receiver_mode_)

    uint32_t start = millis();

    // Wait for data to be received
    while (!loopRFReceiver()) {
        if (millis() - start > 2000) {
            Serial.println("Timeout waiting for data");
            break;
        }
    }

    #else

    delay(1000);

    #endif

}