#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "MorseLed.h"

const char * ssid = "RTAX999";
const char * password = "LiDoDa#959285$";

//IPAddress serverIP (192,168,50,154);
//int port = 1051;
IPAddress serverIP (192,168,50,159);
int port = 2457;

AsyncUDP udp;

static String msg;

void setup() {
  Serial.begin(115200);

  MorseLed morseLed;
  morseLed.setLedPin(8); // Example pin number
  morseLed.execute("SOS");
  morseLed.execute("SOS");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
  if (udp.connect(serverIP, port)) {
    Serial.println("UDP connected");
    msg = WiFi.localIP().toString();
    Serial.println(msg);

    morseLed.execute(msg);

    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      msg += "UDP Packet Type: ";
      msg += packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast";
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      msg += ", From: ";
      msg += packet.remoteIP().toString();
      msg += ":";
      msg += packet.remotePort();
      msg += ", To: ";
      msg += packet.localIP().toString();
      msg += ":";
      msg += packet.localPort();
      msg += ", ms: ";
      msg += String (millis());
      msg += ", Length: ";
      msg += packet.length();
      msg += ", Data: ";
      msg += String((char*)packet.data(), packet.length());
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
      msg += "\n Got " + String (packet.length()) + " bytes of data\n";
      packet.print(msg);
    });
    //Send unicast
    udp.print(msg);
  }
}

void loop() {
  delay(1000);
  //Send broadcast on port 1051
  udp.broadcastTo("Anyone here?", port);
}
