// EEPROMHandle.cpp


/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 */
#include <Arduino.h>
//#include <EEPROM.h>
//#include "EEPROMHandle.h"

#define LED_Pin PC13

void setupEEPROMHandle() {
    // initialize the LED pin as an output.
    pinMode(LED_Pin, OUTPUT);

    /***
      Iterate through each byte of the EEPROM storage.

      Larger AVR processors have larger EEPROM sizes, E.g:
      - Arduno Duemilanove: 512b EEPROM storage.
      - Arduino Uno:        1kb EEPROM storage.
      - Arduino Mega:       4kb EEPROM storage.

      Rather than hard-coding the length, you should use the pre-provided length function.
      This will make your code portable to all AVR processors.
    ***/

    // for (int i = 0; i < EEPROM.length(); i++) {
    //     EEPROM.write(i, 0);
    // }

    // turn the LED on when we're done
    digitalWrite(LED_Pin, HIGH);
    Serial.println ("STM32F411C setup done.");
}

void loopEEPROMHandle() {
    /** Empty loop. **/
    static uint32_t lastTS = 0;
    static bool ledStatus = true;
    uint32_t currTS = millis ();
    if (currTS - lastTS > 200) {
        lastTS = currTS;
        if (ledStatus)
            digitalWrite(LED_Pin, HIGH);
        else
            digitalWrite(LED_Pin, LOW);
        ledStatus = !ledStatus;
        Serial.print ("STM32F411C loop:");
        Serial.println (currTS);
    }
}
