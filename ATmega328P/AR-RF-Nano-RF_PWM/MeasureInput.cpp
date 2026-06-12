// MeasureInput.cpp
#include <Arduino.h>
#include "MeasureInput.h"

struct EdgeRecord
{
    uint32_t delta_usec;
    bool stateInput;
};

volatile EdgeRecord edgeBuf[10];
volatile uint8_t writeIndex = 0;
volatile uint32_t lastTime = 0;

const uint8_t inputPin = 2;   // INT0 (D2)

void edgeISR()
{
    uint32_t now = micros();

    edgeBuf[writeIndex].delta_usec = now - lastTime;
    edgeBuf[writeIndex].stateInput = digitalRead(inputPin);

    lastTime = now;
    writeIndex = (writeIndex + 1) % 10;
}

void setupMeasureInput()
{
    Serial.begin(115200);

    pinMode(inputPin, INPUT);

    lastTime = micros();

	memset(edgeBuf, 0, sizeof(edgeBuf));

    attachInterrupt(digitalPinToInterrupt(inputPin), edgeISR, CHANGE);
}

void loopMeasureInput()
{
    static uint32_t lastDump = 0;

    if (millis() - lastDump >= 1000)
    {
        lastDump += 1000;

        // Make a local copy while interrupts are disabled
        EdgeRecord copy[10];
        uint8_t idx;

        noInterrupts();

        idx = writeIndex;
        for (uint8_t i = 0; i < 10; i++) {
            copy[i].delta_usec = edgeBuf[i].delta_usec;
            copy[i].stateInput = edgeBuf[i].stateInput;
        }

        interrupts();

        Serial.println(F("---- Circular Buffer ----"));

        // Print oldest -> newest
        for (uint8_t i = 0; i < 10; i++)
        {
            uint8_t p = (idx + i) % 10;

            Serial.print(i);
            Serial.print(F(": dt="));
            Serial.print(copy[p].delta_usec);
            Serial.print(F(" us  state="));
            Serial.println(copy[p].stateInput ? "HIGH" : "LOW");
        }

        Serial.println();
    }
}
