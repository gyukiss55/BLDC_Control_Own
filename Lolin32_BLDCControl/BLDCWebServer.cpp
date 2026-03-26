// BLDCWebServer.cpp
#include "BLDCWebServer.h"
#include "BLDCControl.h"

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";

//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";


WebServer server(80);

// Parameters
uint32_t period = 100; // range 10–100
uint32_t duty = 0;     // range 0–50

// HTML page
String htmlPage() {
    String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>BLDC Web Service</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>BLDC Web Service</h2>

  <label>BLDC Period:</label><br>
  <input type="number" id="period" min="10" max="100" value=")rawliteral";

    page += String(period);   // <-- inject current value

    page += R"rawliteral("><br><br>

  <label>PWM duty:</label><br>
  <input type="number" id="duty" min="0" max="50" value=")rawliteral";

    page += String(duty);     // <-- inject current value

    page += R"rawliteral("><br><br>

  <button onclick="change('period', 1)">Period +</button>
  <button onclick="change('period', -1)">Period -</button><br><br>

  <button onclick="change('duty', 1)">Duty +</button>
  <button onclick="change('duty', -1)">Duty -</button>
  <button onclick="reset('duty')">Reset Duty</button>

<script>
function sendUpdate() {
  let p = document.getElementById('period').value;
  let d = document.getElementById('duty').value;

  fetch(`/update?period=${p}&duty=${d}`);
}

function change(id, delta) {
  let el = document.getElementById(id);
  let min = parseInt(el.min);
  let max = parseInt(el.max);
  let val = parseInt(el.value);

  val += delta;
  if (val < min) val = min;
  if (val > max) val = max;

  el.value = val;
  sendUpdate();
}

function reset(id) {
  let el = document.getElementById(id);
  let min = parseInt(el.min);
  el.value = min;
  sendUpdate();
}

document.addEventListener("DOMContentLoaded", () => {
  document.getElementById('period').addEventListener('change', sendUpdate);
  document.getElementById('duty').addEventListener('change', sendUpdate);
});
</script>

</body>
</html>
)rawliteral";

    return page;
}

// Root page
void handleRoot() {
    period = getBLDCPeriod();
    duty = getPWMDuty();
    server.send(200, "text/html", htmlPage());
}

// Update handler
void handleUpdate() {
    if (server.hasArg("period")) {
        int p = server.arg("period").toInt();
        if (p >= 10 && p <= 100) {
            period = p;
            setBLDCPeriod(period);
        }
    }

    if (server.hasArg("duty")) {
        int d = server.arg("duty").toInt();
        if (d >= 0 && d <= 50) {
            duty = d;
            setPWMDuty(duty);
        }
    }

    Serial.printf("Updated -> Period: %d, Duty: %d\n", period, duty);

    server.send(200, "text/plain", "OK");
}

void setupWebServer() {


    WiFi.begin(ssid, password);
    Serial.print("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/update", handleUpdate);

    server.begin();
}

void loopWebServer() {
    server.handleClient();
}
