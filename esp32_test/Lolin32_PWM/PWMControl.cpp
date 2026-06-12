// PWMControl.cpp - Library for controlling PWM on Lolin32
#include <Arduino.h>
#include "PWMControl.h"

const int pwmPins[4] = { 22, 19, 23, 18 };
//const int pwmCh[4] = { 0, 1, 2, 3 };

const uint32_t PWM_FREQ = 10;      // 10 Hz
const uint8_t PWM_RES = 14;      // 14-bit resolution

const uint32_t MAX_DUTY = (1UL << PWM_RES) - 1;

void serialTask();

void setPulseUS(int channel, uint32_t pulse_us)
{
    if (channel < 1 || channel > 4)
        return;

    if (pulse_us < 1000)
        pulse_us = 1000;

    if (pulse_us > 2000)
        pulse_us = 2000;

    // Period = 100000 us
    uint32_t duty =
        (uint64_t)pulse_us * MAX_DUTY / 100000ULL;

    ledcWrite(pwmPins[channel - 1], duty);

    Serial.print("Channel ");
    Serial.print(channel);
    Serial.print(" Pulse: ");
    Serial.println(pulse_us);
}

void setupPWMControl()
{
    Serial.begin(115200);

    for (int i = 0; i < 4; i++)
    {
        ledcAttach(pwmPins[i], PWM_FREQ, PWM_RES);
    }

    // Initial values
    setPulseUS(1, 1000);
    setPulseUS(2, 1000);
    setPulseUS(3, 1000);
    setPulseUS(4, 1000);

	Serial.println("PWM Control Ready");
}

void loopPWMControl()
{
	serialTask();
}

String rx;

void parseCommand(String s)
{
    int pos = 0;

    while (pos < s.length())
    {
        int comma = s.indexOf(',', pos);
        if (comma < 0)
            comma = s.length();

        String tok = s.substring(pos, comma);

        int colon = tok.indexOf(':');

        if (colon > 0)
        {
            int ch = tok.substring(0, colon).toInt();
            int val = tok.substring(colon + 1).toInt();

            if (val < 0) val = 0;
            if (val > 1000) val = 1000;

            setPulseUS(ch, 1000 + val);
        }

        pos = comma + 1;
    }
}

void serialTask()
{
    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\n' || c == '\r')
        {
            if (rx.length())
            {
                parseCommand(rx);
                rx = "";
            }
        }
        else
        {
            rx += c;
        }
    }
}
