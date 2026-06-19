// WifiConnect.cpp

#include <Arduino.h>

#include <WiFi.h>

#ifndef STASSID
#define STASSID "ASUS_98_2G"
#define STAPSK "LiDoDa#959285$"
#endif


void setupWifiConnect() {
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());

}

