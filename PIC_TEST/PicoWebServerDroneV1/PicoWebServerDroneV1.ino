#include <WiFi.h>
#include <WebServer.h>

#define STASSID "ASUS_98_2G"
#define STAPSK "LiDoDa#959285$"

const char* ssid = STASSID;
const char* password = STAPSK;

WebServer server(80);

// ==== SENSOR VALUES ====
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

// ==== PWM VALUES ====
int p_pwm1=1000, p_pwm2=1000, p_pwm3=1000, p_pwm4=1000;

// ==== HTML ====
String htmlPage() {
String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">

<script>
function sendAll() {
  let url = "/?pwm1="+pwm1.value+
            "&pwm2="+pwm2.value+
            "&pwm3="+pwm3.value+
            "&pwm4="+pwm4.value;
  window.location.href = url;
}

function sendOne(id) {
  let el = document.getElementById(id);
  window.location.href = "/?"+id+"="+el.value;
}

function add(id, val) {
  let el = document.getElementById(id);
  el.value = parseInt(el.value) + val;
  sendOne(id);
}

function addAll(val) {
  pwm1.value = parseInt(pwm1.value)+val;
  pwm2.value = parseInt(pwm2.value)+val;
  pwm3.value = parseInt(pwm3.value)+val;
  pwm4.value = parseInt(pwm4.value)+val;
  sendAll();
}
</script>
</head>

<body>

<h3>SENSORS</h3>
Accel: %AX% %AY% %AZ%<br>
Gyro: %GX% %GY% %GZ%<br>
Magn: %MX% %MY% %MZ%<br>
Pressure: %PRESS%<br>
Altitude: %ALT%<br>
Temp1: %T1%<br>
Temp2: %T2%<br>
Lat: %LAT%<br>
Long: %LONG%<br>
Sat: %SAT%<br>

<h3>PWM</h3>

PWM1 <input id="pwm1" value="%PWM1%">
<button onclick="sendOne('pwm1')">Update</button>
<button onclick="add('pwm1',1)">+1</button>
<button onclick="add('pwm1',10)">+10</button>
<button onclick="add('pwm1',100)">+100</button>
<button onclick="add('pwm1',-1)">-1</button>
<button onclick="add('pwm1',-10)">-10</button>
<button onclick="add('pwm1',-100)">-100</button>
<br><br>

PWM2 <input id="pwm2" value="%PWM2%">
<button onclick="sendOne('pwm2')">Update</button>
<button onclick="add('pwm2',1)">+1</button>
<button onclick="add('pwm2',10)">+10</button>
<button onclick="add('pwm2',100)">+100</button>
<button onclick="add('pwm2',-1)">-1</button>
<button onclick="add('pwm2',-10)">-10</button>
<button onclick="add('pwm2',-100)">-100</button>
<br><br>

PWM3 <input id="pwm3" value="%PWM3%">
<button onclick="sendOne('pwm3')">Update</button>
<button onclick="add('pwm3',1)">+1</button>
<button onclick="add('pwm3',10)">+10</button>
<button onclick="add('pwm3',100)">+100</button>
<button onclick="add('pwm3',-1)">-1</button>
<button onclick="add('pwm3',-10)">-10</button>
<button onclick="add('pwm3',-100)">-100</button>
<br><br>

PWM4 <input id="pwm4" value="%PWM4%">
<button onclick="sendOne('pwm4')">Update</button>
<button onclick="add('pwm4',1)">+1</button>
<button onclick="add('pwm4',10)">+10</button>
<button onclick="add('pwm4',100)">+100</button>
<button onclick="add('pwm4',-1)">-1</button>
<button onclick="add('pwm4',-10)">-10</button>
<button onclick="add('pwm4',-100)">-100</button>

<br><br>

<h3>ALL PWM</h3>
<button onclick="addAll(1)">ALL +1</button>
<button onclick="addAll(10)">ALL +10</button>
<button onclick="addAll(100)">ALL +100</button>
<button onclick="addAll(-1)">ALL -1</button>
<button onclick="addAll(-10)">ALL -10</button>
<button onclick="addAll(-100)">ALL -100</button>

<br><br>
<button onclick="sendAll()">UPDATE PWM</button>

</body>
</html>
)rawliteral";

  // replace values
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

// ==== HANDLE REQUEST ====
void handleRoot() {

  if (server.hasArg("pwm1")) p_pwm1 = constrain(server.arg("pwm1").toInt(), 1000, 2000);
  if (server.hasArg("pwm2")) p_pwm2 = constrain(server.arg("pwm2").toInt(), 1000, 2000);
  if (server.hasArg("pwm3")) p_pwm3 = constrain(server.arg("pwm3").toInt(), 1000, 2000);
  if (server.hasArg("pwm4")) p_pwm4 = constrain(server.arg("pwm4").toInt(), 1000, 2000);

  server.send(200, "text/html", htmlPage());
}

// ==== SETUP ====
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

// ==== LOOP ====
void loop() {
  static uint32_t lastTS = 0;
  server.handleClient();
  if (millis() - lastTS > 1000) {
    lastTS += 1000;
    Serial.print (millis ());
    Serial.print(" PWM:");
    Serial.print (p_pwm1);
    Serial.print(",");
    Serial.print (p_pwm2);
    Serial.print(",");
    Serial.print (p_pwm3);
    Serial.print(",");
    Serial.print (p_pwm4);
    Serial.println(" ");
  }
}