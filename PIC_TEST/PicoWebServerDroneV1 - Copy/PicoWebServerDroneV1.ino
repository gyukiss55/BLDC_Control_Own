#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";

WebServer server(80);

// ==== YOUR VARIABLES ====
float p_a_x=1, p_a_y=2, p_a_z=3;
float p_g_x=4, p_g_y=5, p_g_z=6;
float p_m_x=7, p_m_y=8, p_m_z=9;
float p_press=1013;
float p_alt=120;
float p_temp1=25;
float p_temp2=26;
float p_lat=47.0;
float p_long=19.0;
int   p_satNum=10;

int p_pwm1=1000, p_pwm2=1000, p_pwm3=1000, p_pwm4=1000;

// ==== HTML PAGE ====
String htmlPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<script>
function sendPWM(params) {
  window.location.href = "/?" + params;
}

function updateAndSend(id, delta) {
  let el = document.getElementById(id);
  el.value = parseInt(el.value) + delta;
  sendPWM(id + "=" + el.value);
}
</script>
</head>
<body>

<h2>SENSOR DATA</h2>

Accel: %AX% %AY% %AZ% <br>
Gyro: %GX% %GY% %GZ% <br>
Magn: %MX% %MY% %MZ% <br>
Pressure: %PRESS% <br>
Altitude: %ALT% <br>
Temp1: %T1% <br>
Temp2: %T2% <br>
Lat: %LAT% <br>
Long: %LONG% <br>
Sat: %SAT% <br>

<h2>PWM CONTROL</h2>

PWM1: <input id="pwm1" value="%PWM1%"> 
<button onclick="sendPWM('pwm1='+pwm1.value)">Update</button>
<button onclick="updateAndSend('pwm1',1)">+1</button>
<button onclick="updateAndSend('pwm1',10)">+10</button>
<button onclick="updateAndSend('pwm1',100)">+100</button>
<button onclick="updateAndSend('pwm1',-1)">-1</button>
<button onclick="updateAndSend('pwm1',-10)">-10</button>
<button onclick="updateAndSend('pwm1',-100)">-100</button>
<br><br>

PWM2: <input id="pwm2" value="%PWM2%"> 
<button onclick="sendPWM('pwm2='+pwm2.value)">Update</button>
<button onclick="updateAndSend('pwm2',1)">+1</button>
<button onclick="updateAndSend('pwm2',10)">+10</button>
<button onclick="updateAndSend('pwm2',100)">+100</button>
<button onclick="updateAndSend('pwm2',-1)">-1</button>
<button onclick="updateAndSend('pwm2',-10)">-10</button>
<button onclick="updateAndSend('pwm2',-100)">-100</button>
<br><br>

PWM3: <input id="pwm3" value="%PWM3%"> 
<button onclick="sendPWM('pwm3='+pwm3.value)">Update</button>
<button onclick="updateAndSend('pwm3',1)">+1</button>
<button onclick="updateAndSend('pwm3',10)">+10</button>
<button onclick="updateAndSend('pwm3',100)">+100</button>
<button onclick="updateAndSend('pwm3',-1)">-1</button>
<button onclick="updateAndSend('pwm3',-10)">-10</button>
<button onclick="updateAndSend('pwm3',-100)">-100</button>
<br><br>

PWM4: <input id="pwm4" value="%PWM4%"> 
<button onclick="sendPWM('pwm4='+pwm4.value)">Update</button>
<button onclick="updateAndSend('pwm4',1)">+1</button>
<button onclick="updateAndSend('pwm4',10)">+10</button>
<button onclick="updateAndSend('pwm4',100)">+100</button>
<button onclick="updateAndSend('pwm4',-1)">-1</button>
<button onclick="updateAndSend('pwm4',-10)">-10</button>
<button onclick="updateAndSend('pwm4',-100)">-100</button>

</body>
</html>
)rawliteral";

  // Replace placeholders
  page.replace("%AX%", String(p_a_x));
  page.replace("%AY%", String(p_a_y));
  page.replace("%AZ%", String(p_a_z));

  page.replace("%GX%", String(p_g_x));
  page.replace("%GY%", String(p_g_y));
  page.replace("%GZ%", String(p_g_z));

  page.replace("%MX%", String(p_m_x));
  page.replace("%MY%", String(p_m_y));
  page.replace("%MZ%", String(p_m_z));

  page.replace("%PRESS%", String(p_press));
  page.replace("%ALT%", String(p_alt));
  page.replace("%T1%", String(p_temp1));
  page.replace("%T2%", String(p_temp2));

  page.replace("%LAT%", String(p_lat));
  page.replace("%LONG%", String(p_long));
  page.replace("%SAT%", String(p_satNum));

  page.replace("%PWM1%", String(p_pwm1));
  page.replace("%PWM2%", String(p_pwm2));
  page.replace("%PWM3%", String(p_pwm3));
  page.replace("%PWM4%", String(p_pwm4));

  return page;
}

// ==== HANDLE ROOT ====
void handleRoot() {

  if (server.hasArg("pwm1")) p_pwm1 = constrain(server.arg("pwm1").toInt(), 1000, 2000);
  if (server.hasArg("pwm2")) p_pwm2 = constrain(server.arg("pwm2").toInt(), 1000, 2000);
  if (server.hasArg("pwm3")) p_pwm3 = constrain(server.arg("pwm3").toInt(), 1000, 2000);
  if (server.hasArg("pwm4")) p_pwm4 = constrain(server.arg("pwm4").toInt(), 1000, 2000);

  server.send(200, "text/html", htmlPage());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.println("Wifi setup start...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  } 

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
  static uint32_t lastTS = 0;
  if (millis() - lastTS > 1000) {
    lastTS += 1000;
    Serial.print(millis());
    Serial.print(" PWM:");
    Serial.print(p_pwm1);
    Serial.print(",");
    Serial.print(p_pwm2);
    Serial.print(",");
    Serial.print(p_pwm3);
    Serial.print(",");
    Serial.print(p_pwm4);
    Serial.println("");
    
  }
}