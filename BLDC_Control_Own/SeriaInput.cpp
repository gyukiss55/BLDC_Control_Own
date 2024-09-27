// SeriaInput.cpp

#include <Arduino.h>

#include "ESCControl.h"
#include "ADCData.h"

String serialInput;


void setupSerial()
{
    Serial.begin(115200);
    delay(2000);
}

bool ReadPeriodAndPulse (String& str)
{        
    int pos1 = str.indexOf(',');
    int period = -1;
    int pulse = -1;
    if (pos1 > 0 && pos1 < str.length()) {
        String str1 = str.substring(0, pos1);
        String str2 = str.substring(pos1 + 1);
        period = str1.toInt();
        pulse = str2.toInt();
        if (period > 0 && pulse >= 0) {
            pulse = (period * pulse) / 100;

            Serial.print("Period:");
            Serial.print(period);
            Serial.print(", Pulse:");
            Serial.println(pulse);

            SetNextPeriodPulse(period, pulse);
            return true;
        }
        else {
            Serial.print("Error:");
            Serial.print(str1);
            Serial.print("=");
            Serial.print(period);
            Serial.print(",");
            Serial.print(str2);
            Serial.print("=");
            Serial.print(pulse);
        }
    }
    return false;
}

bool ReadPeriodPulseAndNumber(String& str)
{
    int pos1 = str.indexOf(',');
    int period = -1;
    int pulse = -1;
    int number = -1;
    if (pos1 > 0 && pos1 < str.length()) {
        String str1 = str.substring(0, pos1);
        int pos2 = str.indexOf(',', pos1 + 1);
        if (pos2 > 0 && pos2 < str.length()) {
            String str2 = str.substring(pos1 + 1, pos2);
            String str3 = str.substring(pos2 + 1);
            period = str1.toInt();
            pulse = str2.toInt();
            number = str3.toInt();
            if (period > 0 && pulse >= 0 && number > 0) {
                pulse = (period * pulse) / 100;

                Serial.print("Period:");
                Serial.print(period);
                Serial.print(", Pulse:");
                Serial.print(pulse);

                Serial.print(", Number:");
                Serial.println(number);

                SetPeriodPulseNumber(period, pulse, number);
                return true;
            }
            Serial.print("Error:");
            Serial.print(str1);
            Serial.print("=");
            Serial.print(period);
            Serial.print(",");
            Serial.print(str2);
            Serial.print("=");
            Serial.print(pulse);
        }
    }
    return false;
}


void loopSerial()
{

    if (Serial.available()) {
        char ch = Serial.read();
        serialInput.concat(ch);
        Serial.write(ch);
    }
    String str = serialInput;
    if (str.length() > 0 && (str.endsWith("\n")/* || str.endsWith("\r")*/)) {
        serialInput.remove(0);
        int pos = str.indexOf("PP:");
        if (pos < str.length()) {
            String str1 = str.substring (pos + 3);
            ReadPeriodAndPulse (str1);
            return;
        } 
        pos = str.indexOf("PPN:");
        if (pos < str.length()) {
            String str1 = str.substring(pos + 4);
            ReadPeriodPulseAndNumber(str1);
            return;
        }
    }
}
