// BLDCExternalInterrupt.h
#ifndef BLDC_EXTERNAL_INTERRUPT_H
#define BLDC_EXTERNAL_INTERRUPT_H
#include <Arduino.h>

class BLDCExternalInterrupt {
public:
    void begin(int pin);
    float getRPM();
    int getDirection();

private:
    static void IRAM_ATTR isr();

    static volatile uint32_t lastTime;
    static volatile uint32_t period;
    static volatile int direction;
};

#endif