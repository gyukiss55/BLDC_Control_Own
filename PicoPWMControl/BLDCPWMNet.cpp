// BLDCPWMNet.cpp

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include "CommonData.h"

const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";

//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";

static WebServer server(80);

void handleRoot() {
    String html = "<html><body>";
    html += "<h2>BLDC Web Service</h2>";

    html += "HALL counter:" + String(hallCounter);
    html += " counter/minute:" + String(hallCounterPerMin) + "<br><br>";

    html += "BLDC speed: " + String(speed) + "<br>";
    html += "BLDC speed1: " + String(speed1) + "<br><br>";

    html += "<a href='/set?Speed=" + String(speed + 1) + "'>Speed +</a><br>";
    html += "<a href='/set?Speed=" + String(speed - 1) + "'>Speed -</a><br>";
    html += "<a href='/set?Speed=" + String(speed + 10) + "'>Speed +10</a><br>";
    html += "<a href='/set?Speed=" + String(speed - 10) + "'>Speed -10</a><br>";
    html += "<a href='/set?Speed=6553'>Reset</a><br>";
    html += "<a href='/set?Speed=" + String(speed1) + "'>Speed1</a><br>";

    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleSet() {
    if (server.hasArg("Speed")) {
        int s = server.arg("Speed").toInt();

        if (s < 6553) s = 6553;
        if (s > 13107) s = 13107;

        speed = s;
    }
    server.sendHeader("Location", "/");
    server.send(303);
}

void BLDCPWMNet_init() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);

    server.on("/", handleRoot);
    server.on("/set", handleSet);

    server.begin();
}

void BLDCPWMNet_loop() {
    server.handleClient();
}