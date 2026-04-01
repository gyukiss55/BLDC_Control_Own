// BLDCPWMNet.cpp
#include "BLDCPWMNet.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "BLDCPWMControl.h"

const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";

//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";

static WebServer server (80);

// HTML page
String htmlPage() {
    String page = R"rawliteral(
<!DOCTYPE html>
<html>
<title>BLDC Throttle</title>
</head>
<body>

<h2>Throttle Control</h2>

<input type="range" min="1000" max="2000" value="1000" id="throttle" oninput="update(this.value)">
<p>Throttle: <span id="value">1000</span> µs</p>

<script>
function update(val) {
    document.getElementById("value").innerText = val;

    fetch(`/set?period=20000&duty=${val}`)
        .catch(err => console.error(err));
}
</script>

</body>
</html>
)rawliteral";

    return page;
}


BLDCPWMNet::BLDCPWMNet(BLDCPWMControl* ctrl)
    : control(ctrl) {
	setupWebServer();
}

void BLDCPWMNet::setupWebServer() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());
}

void BLDCPWMNet::begin() {
    server.on("/", [this]() { handleRoot(); });
    server.on("/set", [this]() { handleSet(); });
    server.begin();
}

void BLDCPWMNet::handleClient() {
    server.handleClient();
}

// Root page
void BLDCPWMNet::handleRoot() {
    server.send(200, "text/html", htmlPage());
}


void BLDCPWMNet::handleSet() {
    if (server.hasArg("period") && server.hasArg("duty")) {
        int period = server.arg("period").toInt();
        int duty = server.arg("duty").toInt();

        control->setPWM(period, duty);

        server.send(200, "text/plain", "OK");
    }
    else {
        server.send(400, "text/plain", "Missing args");
    }
}