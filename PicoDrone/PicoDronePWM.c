// PicoDronePWM.c
#include "PicoDronePWM.h"

#include <Arduino.h>

#define PWM_FREQ 100
#define PWM_WRAP 20000   // 20ms period (100Hz)

static uint pwm_pins[4] = { 10, 11, 12, 13 };
static uint slices[4];

void PicoDronePWM_init()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_function(pwm_pins[i], GPIO_FUNC_PWM);
        slices[i] = pwm_gpio_to_slice_num(pwm_pins[i]);

        pwm_set_wrap(slices[i], PWM_WRAP);
        pwm_set_clkdiv(slices[i], 125.0f); // 125MHz / 125 = 1MHz → 1 tick = 1µs

        pwm_set_enabled(slices[i], true);

        PicoDronePWM_set(i, 1000);
    }
}

void PicoDronePWM_set(int ch, uint16_t pulse_us)
{
    if (ch < 0 || ch > 3) return;

    if (pulse_us < 1000) pulse_us = 1000;
    if (pulse_us > 2000) pulse_us = 2000;

    pwm_set_gpio_level(pwm_pins[ch], pulse_us);
}

uint16_t PicoDronePWM_get(int ch)
{
    return pwm_get_counter(slices[ch]);
}
