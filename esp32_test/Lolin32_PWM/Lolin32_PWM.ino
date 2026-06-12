
#include <Arduino.h>
#include "PWMControl.h"
#include "PWMMeasure.h"

void setup()
{
    Serial.begin(115200);
    setupPWMControl();
    setupPWMMeasure();
}

void loop()
{
    loopPWMControl();
    loopPWMMeasure();
    // Example: Sweep from 1000us to 2000us and back
    /*
    for (uint32_t pulse = 1000; pulse <= 2000; pulse += 100)
    {
        setPulseUS(1, pulse);
        setPulseUS(2, pulse);
        setPulseUS(3, pulse);
        setPulseUS(4, pulse);
        delay(500);
    }
    for (uint32_t pulse = 2000; pulse >= 1000; pulse -= 100)
    {
        setPulseUS(1, pulse);
        setPulseUS(2, pulse);
        setPulseUS(3, pulse);
        setPulseUS(4, pulse);
        delay(500);
    }
    */
}