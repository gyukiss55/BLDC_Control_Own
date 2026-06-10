// ESP32_Wifi class implementation for WiFi connection management

#include <Arduino.h>
#include "WiFi.h"

const char* ssid = "RTAX999";
const char* password = "LiDoDa#959285$";

void setupWifi() {
    Serial.begin(115200);
    delay(2000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while (1) {
            delay(1000);
        }
    }
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

}
    