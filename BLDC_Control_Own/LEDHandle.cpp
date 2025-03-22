// LEDHandle.cpp


#include <Arduino.h>

#include "MilliSecDelay.h"
#include "ESCControl.h"


#define LED_Pin PC13

MilliSecDelay delayMS;

uint32_t lastTsSerial = 0;
uint32_t counterSerial = 0;

void printTsSerial ();

void setupLEDHandle() {
    // initialize the LED pin as an output.
    pinMode(LED_Pin, OUTPUT);

 
    // turn the LED on when we're done
    digitalWrite(LED_Pin, HIGH);
    Serial.println ("STM32Fxxx setup done.");
    //delayMS.Restart(200);
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_Pin, HIGH);
      delay(200);
      digitalWrite(LED_Pin, LOW);
      delay(800);
      printTsSerial ();
    }
    lastTsSerial = micros ();
    lastTsSerial = lastTsSerial - (lastTsSerial % 1000);
    Serial.print ("Ts0:");
    Serial.println (lastTsSerial);

}

void printTsSerial ()
{
      uint32_t currTs = micros ();
      Serial.print ("Ts:");
      Serial.print (counterSerial++);
      Serial.print ("=");
      Serial.println (currTs);

}


void loopLEDHandle() {

    static bool ledStatus = true;

    uint32_t curr = micros();

    if (ledStatus && ((curr - lastTsSerial) >= 100000)) {
        digitalWrite(LED_Pin, HIGH);
        lastTsSerial += 100000;
        ledStatus = !ledStatus;
        Serial.print ("Ts1:");
        Serial.println (lastTsSerial);
    }
    else if (!ledStatus && ((curr - lastTsSerial)>= 400000)) {
        digitalWrite(LED_Pin, LOW);
        lastTsSerial += 400000;
        ledStatus = !ledStatus;
        printTsSerial ();
        Serial.print ("Ts2:");
        Serial.println (lastTsSerial);
    }
}
