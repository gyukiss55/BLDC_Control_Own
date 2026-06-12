//PWMMeasure.cpp
#include "Arduino.h"
#include "TimerTrigger.h"

#define PIN_EXT0 12
#define PIN_EXT1 14

struct PWMMeasureStruct
{
	uint32_t id;            // Optional ID for debugging
    uint32_t elapsedTime;  // Time since last change in microseconds
	bool level;           // Current level (HIGH or LOW)
};

PWMMeasureStruct pwm0[32];
PWMMeasureStruct pwm1[32];

static TimerTrigger dumpTrigger; 

void IRAM_ATTR isrExt0()
{
    static uint32_t id = 0;
    static uint32_t lastTime = 0;
    static int8_t wr0 = 0;

    uint32_t now = micros();

    pwm0[wr0].id = ++id;
    pwm0[wr0].elapsedTime = now - lastTime;
    pwm0[wr0].level = gpio_get_level((gpio_num_t)PIN_EXT0);

    lastTime = now;
    wr0 = (wr0 + 1) & 31;      // 32-entry circular buffer
}

void IRAM_ATTR isrExt1()
{
    uint32_t now = micros();

    static uint32_t id = 0;
    static uint32_t lastTime = 0;
    static int8_t wr1 = 0;

    pwm1[wr1].id = ++id;
    pwm1[wr1].elapsedTime = now - lastTime;
    pwm1[wr1].level = gpio_get_level((gpio_num_t)PIN_EXT1);

    lastTime = now;
    wr1 = (wr1 + 1) & 31;
}

void setupPWMMeasure()
{
    Serial.begin(115200);

    pinMode(PIN_EXT0, INPUT);
    pinMode(PIN_EXT1, INPUT);

    attachInterrupt(digitalPinToInterrupt(PIN_EXT0), isrExt0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_EXT1), isrExt1, CHANGE);

	dumpTrigger.begin(1000); // Dump every 1000 ms
}

void loopPWMMeasure()
{
    static uint32_t lastDump = 0;

	if (!dumpTrigger.checkAndStep())
        return;

    if (millis() - lastDump >= 1000)
    {
        lastDump = millis();

        PWMMeasureStruct buf0[32];
        PWMMeasureStruct buf1[32];

        noInterrupts();

        for (int i = 0; i < 32; i++)
        {
            buf0[i].id = pwm0[i].id;
            buf0[i].elapsedTime = pwm0[i].elapsedTime;
            buf0[i].level = pwm0[i].level;

            buf1[i].id = pwm1[i].id;
            buf1[i].elapsedTime = pwm1[i].elapsedTime;
            buf1[i].level = pwm1[i].level;
        }

        interrupts();

        uint8_t idx0 = 0;
        uint8_t idx1 = 0;

        uint32_t id0min = buf0[0].id;
        uint32_t id1min = buf1[0].id;

        for (int i = 1; i < 32; i++)
        {
            if (buf0[i].id < id0min) {
                id0min = buf0[i].id;
				idx0 = i;
            }

			if (buf1[i].id < id1min) {
                id1min = buf1[i].id;
				idx1 = i;
			}
        }

        Serial.print("/ EXT0 =");
        for (int i = 0; i < 32; i++)
        {
            int p = (idx0 + i) & 31;
            if (i == 0) {
			    Serial.print(buf0[p].id);
                Serial.print(";");
            }
            Serial.print(buf0[p].elapsedTime);
            Serial.print("-");
            Serial.print(buf0[p].level ? "H " : "L ");
        }
		Serial.println();

        Serial.print("/ EXT1 =");
        for (int i = 0; i < 32; i++)
        {
            int p = (idx1 + i) & 31;

            if (i == 0) {
                Serial.print(buf1[p].id);
                Serial.print(";");
            }
            Serial.print(buf1[p].elapsedTime);
            Serial.print("-");
            Serial.print(buf1[p].level ? "H " : "L ");
        }
        Serial.println();
    }
}
