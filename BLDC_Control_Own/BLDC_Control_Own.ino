
#include "EEPROMHandle.h"

void setup() {
    Serial.begin (115200);
    delay (2000);
    setupEEPROMHandle ();
}

void loop() {
    
    loopEEPROMHandle ();
}
