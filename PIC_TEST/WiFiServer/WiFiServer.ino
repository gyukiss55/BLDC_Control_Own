
#include <Arduino.h>
#include "UDPServer.h"
//#include "WifiServerClient.h"

void setup() {
    Serial.begin(115200);
    delay(2000);
    setupUDPServer();
    //setupWifiServerClient();
}

void loop() {
    loopUDPServer();
    //loopWifiServerClient();
}