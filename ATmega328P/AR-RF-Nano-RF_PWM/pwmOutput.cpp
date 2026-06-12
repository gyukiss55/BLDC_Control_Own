// pwmOutput.cpp

#include <Arduino.h>
#include "pwmOutput.h"


const uint32_t PERIOD_US = 100000;   // 100 ms

uint32_t pwmValue[2] = { 1000, 1000 };
char* pattern[] = { "1:", "2:" };

void setupPWMOutput()
{
    pinMode(9, OUTPUT);    // OC1A
    pinMode(10, OUTPUT);   // OC1B

    TCCR1A = 0;
    TCCR1B = 0;

    // Fast PWM, TOP = ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // Enable outputs on D9 (OC1A) and D10 (OC1B)
    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);

    // Prescaler = 8 (0.5 µs per timer tick)
    TCCR1B |= (1 << CS11);

    // 100 ms period
    ICR1 = 200000UL - 1;

    // Initial pulse widths
    OCR1A = 1500UL * 2;    // D9 = 1500 µs
    OCR1B = 1000UL * 2;    // D10 = 1000 µs

    Serial.println("Ready to receive commands in the format: <channel>:<value> (e.g. 1:500)");

}

void setValue(uint8_t channel, uint16_t value)
{
    if (value > 1000)
        value = 1000;

    uint16_t pulse_us = 1000 + value;

    Serial.print("Setting channel ");
    Serial.print(channel);
    Serial.print(" to ");
    Serial.print(pulse_us);
    Serial.println(" µs");

    switch (channel)
    {
    case 1:
        OCR1A = pulse_us * 2;   // D9
        break;

    case 2:
        OCR1B = pulse_us * 2;   // D10
        break;

        // Add more channels here if needed
    }
}

void loopPWMOutput()
{
    parseCommand();
}

void parseCommand()
{
    if (Serial.available() > 0) {
        int indexFound = -1;
        String input = Serial.readStringUntil('\n');
        for (int i = 0; i < 2; i++) {
            if (input.startsWith(pattern[i])) {
                input = input.substring(strlen(pattern[i])); // Remove the pattern prefix

                Serial.print("Found pattern: ");
                Serial.println(input);

                int value = input.toInt();
                if (value >= 0 && value <= 1000) {
                    pwmValue[i] = value; // Update the PWM value for the corresponding pin
                    indexFound = i;

                    Serial.print("PWM");
                    Serial.print(i + 1);
                    Serial.print("=");
                    Serial.println(pwmValue[i]);
                    break;

                }
            }
        }
        if (indexFound != -1) {
            Serial.print("Updated PWM");
            Serial.print(indexFound + 1);
            Serial.print("=");
            Serial.println(pwmValue[indexFound]);
            switch (indexFound  ) {
            case 0:
                setValue(1, pwmValue[0]);
                break;
            case 1:
                setValue(2, pwmValue[1]);
                break;
            }
        }
    }
    // Update the PWM outputs with the new values
}
