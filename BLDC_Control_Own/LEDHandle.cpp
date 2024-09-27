// LEDHandle.cpp


#include <Arduino.h>

#include "MilliSecDelay.h"
#include "ESCControl.h"


#define LED_Pin PC13

MilliSecDelay delayMS;

void setupLEDHandle() {
    // initialize the LED pin as an output.
    pinMode(LED_Pin, OUTPUT);

 
    // turn the LED on when we're done
    digitalWrite(LED_Pin, HIGH);
    Serial.println ("STM32Fxxx setup done.");
    delayMS.Restart(200);
}


void loopLEDHandle() {

    static bool ledStatus = true;

    if (delayMS.TestAndSet ()) {
        if (ledStatus)
            digitalWrite(LED_Pin, HIGH);
        else
            digitalWrite(LED_Pin, LOW);
        ledStatus = !ledStatus;
        //Serial.print ("STM32F411C loop:");
        //Serial.println (millis());
    }
}
