// PicoDronePWM.c
#include "PicoDronePWM.h"

#include <Arduino.h>

// 100Hz
#define PWM_FREQ 100

// 10ms period (100Hz)
#define PWM_WRAP 10000

 // 4095 for 12-bit resolution
#define PWMRANGE (((1 << 12)) - 1)

 // 100Hz PWM frequency
#define PWMFREQ_HZ 100

static uint pwm_pins[4] = { 10, 11, 12, 13 };
static uint16_t pwm_pulses[4] = { 1000, 1000, 1000, 1000 }; // 1ms pulse width (1000µs)

void PicoDronePWM_init()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(pwm_pins[i], OUTPUT);
    }
    analogWriteRange(PWMRANGE); // attempt to set 10 bit PWM
    analogWriteFreq(PWMFREQ_HZ);
    for (int i = 0; i < 4; i++)
    {
		uint32_t duty = (pwm_pulses[i] * PWMRANGE) / PWM_WRAP; // Convert pulse width to duty cycle
        analogWrite(pwm_pins[i], duty);
    }
}

void PicoDronePWM_set(int ch, uint16_t pulse_us)
{
	pwm_pulses[ch] = pulse_us;
    uint32_t duty = (pwm_pulses[ch] * PWMRANGE) / PWM_WRAP; // Convert pulse width to duty cycle
    analogWrite(pwm_pins[ch], duty);
}

uint16_t PicoDronePWM_get(int ch)
{
    return pwm_pulses[ch];
}
