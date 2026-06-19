// WifiServerClient.cpp
// Placed in the public domain by Earle F. Philhower, III, 2022

#include <Arduino.h>
#include <WiFi.h>

#include "WifiConnect.h"

int port = 4242;

WiFiServer server(port);

void setupWifiServerClient() {
	setupWifiConnect();
    server.begin();
}

void loopWifiServerClient() {
    static int i;
    delay(1000);
    Serial.printf("--loop %d\n", ++i);
    delay(10);
    WiFiClient client = server.accept();
    if (!client) {
        return;
    }
    client.println("Type anything and hit return");
    while (!client.available()) {
        delay(10);
    }
    String req = client.readStringUntil('\n');
    Serial.println(req);
    client.printf("Hello from Pico-W\r\n");
    client.flush();
}
