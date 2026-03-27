#include "WifiNet.h"
#include "OledDisp.h"
#include "PwmSignal.h"


void setup() {
    Serial.begin(115200);
    delay(1000);
    setupWifi();
    oledInit();
    pwmInit();
}

void loop() {
    static uint32_t last = 0;

    struct tm timeinfo;

    if (millis() - last > 1000) {
        String dateStr, timeStr;
        if (getDateTime(dateStr, timeStr)) {
            displayText(dateStr, timeStr);
        }
        last = millis();
        Serial.print(timeStr);
        Serial.print(" / ");
        Serial.println(dateStr);
    }

    pwmUpdate();
}