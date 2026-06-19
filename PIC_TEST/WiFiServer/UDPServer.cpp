// UDPServer.cpp


#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "WifiConnect.h"


unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged\r\n";        // a string to send back

WiFiUDP Udp;

void setupUDPServer() {
    Serial.begin(115200);
	setupWifiConnect();
    Serial.printf("UDP server on port %d\n", localPort);
    Udp.begin(localPort);
}

void loopUDPServer() {
    // if there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d)\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort(), Udp.destinationIP().toString().c_str(), Udp.localPort());

        // read the packet into packetBufffer
        int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        packetBuffer[n] = 0;
        Serial.println("Contents:");
        Serial.println(packetBuffer);

        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
    }
}

/*
  test (shell/netcat):
  --------------------
    nc -u 192.168.50.144 8888
*/
