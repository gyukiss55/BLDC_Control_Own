// Placed in the public domain by Earle F. Philhower, III, 2022

#include <WiFi.h>
// ---------- WiFi ----------
const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";


int port = 4242;

WiFiServer server(port);

void setup() {
  Serial.begin(115200);
  delay(5000);

  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  int inByte = 0;
  while (Serial.available() == 0) {
    // get incoming byte:
    delay(1000);
    Serial.print("?");
    
  }
  inByte = Serial.read();

  String log = "\nConnecting to " + String ( ssid) + " with " + String(password) + " \n";
  Serial.print(log);

  WiFi.mode(WIFI_STA);
  WiFi.setHostname("PicoW2");

  int nr = 500;

  WiFi.begin(ssid, password);

  for(int i = 0; i < nr; i++) {
    bool connected = false;
    
    unsigned long ts = millis();

    while (millis() - ts < 5000) {
      if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        break;
      }
      delay(500);
      Serial.print(i);
      Serial.print(".");
    }

    if (connected)
      break;
    else {
      WiFi.disconnect();   // disconnect from AP
      WiFi.end();          // shut down WiFi hardware
      delay(2000);    
    }


  }

  Serial.printf("\nConnected to WiFi\n\nConnect to server at %s:%d\n", WiFi.localIP().toString().c_str(), port);

  server.begin();
}

void loop() {
  static int i;
  delay(1000);
  Serial.print(++i);
  if ( i % 50 == 0)
    Serial.println();
  delay(10);
  WiFiClient client = server.accept();
  if (!client) {
    return;
  }
  client.println("Type anything and hit return");
  while (!client.available()) {
    delay(10);
  }
  String req = client.readStringUntil('\n');
  Serial.println(req);
  client.printf("Hello from Pico-W\r\n");
  client.flush();
}
