// ESP32_AsyncUDPServer.cpp
#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "ESP32_Wifi.h"

AsyncUDP udp;
const unsigned int localPort = 1234;

void setupAsyncUDPServer() {
    setupWifi();
    if (udp.listen(localPort)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %lu bytes of data", (unsigned long)packet.length());
            });
    }
}

void loopAsyncUDPServer() {
    delay(1000);
    //Send broadcast
    udp.broadcast("Anyone here?");
}
