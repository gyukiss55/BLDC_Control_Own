

#include <Arduino.h>

#include "LEDHandle.h"
#include "ESCControl.h"
#include "SeriaInput.h"
#include "ADCData.h"

void setup()
{
    setupSerial();
    setupLEDHandle ();
    setupESCControl ();
    setupADC();
}

void loop()
{
    loopSerial();
    loopLEDHandle ();
    //loopESCControl ();
    loopADC();
}
