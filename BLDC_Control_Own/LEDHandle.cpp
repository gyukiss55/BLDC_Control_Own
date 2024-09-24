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

static String serialInput;

void loopSerial() {

    if (Serial.available()) {
        char ch = Serial.read();
        serialInput.concat(ch);
        Serial.write(ch);
    }
    String str = serialInput;
    if (str.length() > 0 && (str.endsWith("\n")/* || str.endsWith("\r")*/) ) {
        serialInput.remove(0);
        // Serial.print("Rec<");
        // Serial.print(str);
        // Serial.println(">");
        int pos1 = str.indexOf(',');
        int period = -1;
        int pulse = -1;
        if (pos1 > 0 && pos1 < str.length()) {
            String str1 = str.substring(0, pos1);
            String str2 = str.substring(pos1 + 1);
            period = str1.toInt();
            pulse = str2.toInt();
            if (period > 0 && pulse >=0) {
                Serial.print("Period:");
                Serial.print(period);
                Serial.print(", Pulse:");
                Serial.println(pulse);
                SetNextPeriodPulse(period, (period * 100) / pulse);
            } else {
                Serial.print("Error:");
                Serial.print(str1);
                Serial.print("=");
                Serial.print(period);
                Serial.print(",");
                Serial.print(str2);
                Serial.print("=");
                Serial.print(pulse);
            }
        }
    }
}

void loopLEDHandle() {

    static bool ledStatus = true;

    loopSerial ();  
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
