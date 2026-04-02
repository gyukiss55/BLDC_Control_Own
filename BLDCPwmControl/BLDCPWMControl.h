// BLDCPWMControl.h
#ifndef BLDC_PWM_CONTROL_H
#define	BLDC_PWM_CONTROL_H
#include <Arduino.h>

class BLDCPWMControl {
public:
    void begin(int pin, int period = 20000, int duty = 1000);
    void setPWM(int period_us, int duty_us);
	int period() const { return pwmPeriod; }
	int duty() const { return pwmDuty; }

private:
    int pwmPin;
    int pwmPeriod;
    int pwmDuty;
    void setPWM();
};

#endif
