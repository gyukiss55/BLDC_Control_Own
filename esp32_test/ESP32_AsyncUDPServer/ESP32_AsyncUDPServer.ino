#include "WiFi.h"
#include "AsyncUDP.h"
#include "OledDisplay.h"

const char * ssid = "RTAX999";
const char * password = "LiDoDa#959285$";

const int udpPort = 1051;

AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    delay(2000);
    while (!Serial) {
          // some boards need to wait to ensure access to serial over USB
    }

    setupOLED();

    Serial.println(F("\nwait 1. 100 ms ..."));
    uint32_t ms = millis();
    while (millis() - ms < 1000);
      
    Serial.println(F("\nwait 2.0 100 ms ...")); 
    //Connect to the WiFi network
      
    Serial.println("WiFi.begin start");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
    OledDisplay (WiFi.localIP().toString());
    if(udp.listen(udpPort)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
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
            //String reply = "ESP32 UDP Server got " + String (packet.length()) +  "bytes of data\n";
            AsyncUDPMessage msg;
            msg.printf("ESP32 UDP Server got %u bytes of data", packet.length());
            packet.send (msg);
            //packet.printf("Got %u bytes of data: %s", packet.length(), String (packet.data(), packet.length()).ToStr());
            //packet.flush ();
            OledDisplay (String (packet.data(), packet.length()));
        });
    }
}

void loop()
{
    delay(1000);
    //Send broadcast
    udp.broadcast("Anyone here?");
}
