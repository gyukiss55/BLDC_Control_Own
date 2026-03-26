
//BLDCSerial.cpp - BLDC Motor Control with Serial Communication
#include "BLDCSerial.h"
#include "BLDCControl.h"

//#define LED_BUILTIN 22

// ---------------- SERIAL COMMAND ----------------
void handleSerial()
{
    static String input = "";

    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\n')
        {
            uint32_t newBldcPeriod = getBLDCPeriod();
            uint32_t newPwmDuty = getPWMDuty();
            bool updatePending = false;
            if (input.startsWith("p"))
            {
                newBldcPeriod = input.substring(1).toInt();
                updatePending = true;
            }
            else if (input.startsWith("d"))
            {
                newPwmDuty = constrain(input.substring(1).toInt(), 0, 1023);
                updatePending = true;
            }
            else if (input.startsWith("-p")) {
                newBldcPeriod -= 5;
                updatePending = true;
            }
            else if (input.startsWith("+p")) {
                newBldcPeriod += 5;
                updatePending = true;
            }
            else if (input.startsWith("-d")) {
                newPwmDuty -= 5;
                updatePending = true;
            }
            else if (input.startsWith("+d")) {
                newPwmDuty += 5;
                updatePending = true;
            }
            if (updatePending) {
                setBLDCPeriod(newBldcPeriod);
                setPWMDuty(newPwmDuty);
            }
            input = "";
        }
        else
        {
            input += c;
        }
    }
}

void setupSerial() {
	Serial.begin(115200);
    delay(2000);
	pinMode(LED_BUILTIN, OUTPUT);
}

void loopSerial()
{
    static uint32_t lastPrint = 0;
    static bool led_builtin_off = false;

    handleSerial();

    if (millis() - lastPrint >= 1000)
    {
        digitalWrite(LED_BUILTIN, LOW);
        led_builtin_off = true;
        lastPrint = millis();

        Serial.print("ms: ");
        Serial.print(millis());
        Serial.print(" duty: ");
        Serial.print(getPWMDuty());
        Serial.print(" period: ");
        Serial.print(getBLDCPeriod());
        Serial.print(" extIntCnt: ");
        Serial.println(getExtIntCounter());
        //digitalWrite(LED_BUILTIN, HIGH);
    }
    if (led_builtin_off && millis() - lastPrint >= 100)
    {
        led_builtin_off = false;
        digitalWrite(LED_BUILTIN, HIGH);
    }
}