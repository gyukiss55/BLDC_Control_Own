

#include <Arduino.h>

#include "LEDHandle.h"
#include "ESCControl.h"

void setup() {
    Serial.begin (115200);
    delay (2000);
    setupLEDHandle ();
    setupESCControl ();
}

void loop() {
    
    loopLEDHandle ();
    loopESCControl ();
}
