// Pico_UDPserver.cpp
/*
  UDPSendReceive.pde:
  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.

  adapted from Ethernet library examples
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
//#define STASSID "ASUS_98_2G"
//#define STASSID "RTAX999"
//#define STAPSK "LiDoDa#959285$"
#define STASSID "HUAWEI P30"
#define STAPSK "6381bf07b666"
#endif

IPAddress ipBradcast(192, 168, 1, 255);
//IPAddress ipServer(192,168,50,180);
//IPAddress ipServer(192,168,50,154);
IPAddress ipServer(192,168,43,1);

unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged\r\n";        // a string to send back

WiFiUDP Udp;

String packetStr = "";

void setupUDPServer() {
    Serial.begin(115200);
    WiFi.end();
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("UDP server on port %d\n", localPort);
    Udp.begin(localPort);
}

void loopUDPServer() {
    if (packetStr.length() > 0) {

        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
    }
}

void setupUDPClient() {
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("UDP client on port %d\n", localPort);
}

void loopUDPClient(unsigned int udpPort) {
    // if there's data available, read a packet
    if (packetStr.length() > 0) {

        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(ipServer, udpPort);
        Udp.write(packetStr.c_str());
        Udp.endPacket();
		packetStr = "";
    }
}

void sendUDPMessage(const String& message) {
    packetStr = message;
    loopUDPClient(8888);
}

/*
  test (shell/netcat):
  --------------------
    nc -u 192.168.pico.address 8888
*/
