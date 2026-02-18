

#include <Arduino.h>

#include "LEDHandle.h"
//#include "ESCControl.h"
#include "SeriaInput.h"
//#include "ADCData.h"
#include "STM32F411PWM6chv3.h"

void setup()
{
    setupSerial();
    setupLEDHandle ();
    //setupESCControl (); 
    //setupADC();
    //setupSTM32F411PWM6chv3 ();
    //setupPWM3V1 ();
}

void loop()
{
    loopSerial();
    loopLEDHandle ();
    //loopESCControl ();
    //loopADC();
    //loopSTM32F411PWM6chv3 ();
    //loopPWM3V1 ();
}
