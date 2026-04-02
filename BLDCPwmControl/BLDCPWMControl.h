// BLDCPWMControl.h
#ifndef BLDC_PWM_CONTROL_H
#define	BLDC_PWM_CONTROL_H
#include <Arduino.h>

class BLDCPWMControl {
public:
    void begin(int pin);
    void setPWM(int period_us, int duty_us);

private:
    int pwmChannel = 0;
    int pwmPin;
};

#endif
