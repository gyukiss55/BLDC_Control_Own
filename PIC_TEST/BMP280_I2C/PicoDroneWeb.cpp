//PicoDroneWeb.c

#include "PicoDroneWeb.h"
#include <Arduino.h>
#include <WiFi.h>

#include "DroneData.h"

const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";

//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";

WiFiServer server(80);

extern GAM_Data gam;
extern GPS_Data gps;

void PicoDroneWeb_init()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(500);

    server.begin();
}

void handlePWM(String req)
{
    // Example: ?p0=1500,p1=1600
    int idx = 0;

    while ((idx = req.indexOf("p")) != -1)
    {
        int ch = req.substring(idx + 1, idx + 2).toInt();
        int val = req.substring(idx + 3).toInt();

        PicoDronePWM_set(ch, val);
        req = req.substring(idx + 1);
    }
}

void PicoDroneWeb_loop()
{
    WiFiClient client = server.available();
    if (!client) return;

    String req = client.readStringUntil('\r');

    if (req.indexOf("?") != -1)
        handlePWM(req);

    String html = R"rawliteral(
        HTTP/1.1 200 OK
        Content-Type: text/html
        
        <h1>PicoDrone Status</h1>
    )rawliteral"; 
	html += "TEMP: " + String(gam.temperature,2) + "<br>";
    html += "PRESS: " + String(gam.pressure,2) + "<br>";
    html += "GPS: " + String(gps.lat, 5) + ", " + String(gps.lon, 5) + ", " + String(gps.sats) + "<br>";
    html += "PWM: ";
    for (int i = 0; i < 4; i++)
        html += String(i+1) + "-" + String(PicoDronePWM_get(i)) + " ";
    html += "<br>";
	client.print(html);

    client.stop();
}
