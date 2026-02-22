#include <Adafruit_NeoPixel.h>

#define LED_PIN 48  // ESP32-S3  onboard RGB LED pin
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("✅ RGB LED test started on GPIO2");

  strip.begin();
  strip.setBrightness(1);
  strip.clear();
  strip.show();
}

byte brightness[]={0,1,5,10,20,40};

void loop() {
  static int loopNr = 0;
  Serial.println("RED");
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(500);

  Serial.println("GREEN");
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  delay(500);

  Serial.println("BLUE");
  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show();
  delay(500);
  loopNr++;
  strip.setBrightness(brightness[loopNr%6]);
  Serial.printf("Brightness:%d\n", brightness[loopNr%6]);
}