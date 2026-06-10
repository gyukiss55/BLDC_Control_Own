/*
  Fibonacci calculation test for Arduino and ESP32.
  Created by Lucas Saavedra Vaz, 2024
*/

// ESP32-C3-DevMode

#include <Arduino.h>

#include "FibonacciTest.h"
#include "WebServer.h"
#include "Parameters.h"


void setup() {

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(2000);
  //setupWebServer(); 
  for (int i = 0; i < 5; i++) {
    digitalWrite (LED_PIN, HIGH);
    Serial.print("Blinking LED:");
    Serial.println(i);
    delay(500);
    digitalWrite (LED_PIN, LOW);
    delay(500);
  }
  //while (!Serial) {
    //delay(10);
  //}
  Serial.println("ESP32-C3-SuperMini Test");
}

void loop1() {
  loopWebServer();
}

void loop() {
  static unsigned long lastTSFibonacci = 0;
  static unsigned long lastTSBlink = 0;
  static bool ledOn = true;
  const unsigned long stepFibonacci = 5000;
  const unsigned long stepBlink = 200;
  unsigned long currTS = millis();
  if (currTS - lastTSFibonacci > stepFibonacci)  {

    int n_run = N_RUNS;
    int n_fibonacci = FIB_N;
    String log;
    FibonacciTest (n_run, n_fibonacci, log);

    lastTSFibonacci += stepFibonacci;
  }
  if (currTS - lastTSBlink > stepBlink)  {
    if  (ledOn) {
      digitalWrite (LED_PIN, HIGH);
    } else {
      digitalWrite (LED_PIN, LOW);
    }
    ledOn = !ledOn;
    lastTSBlink += stepBlink;
  }
  

  //vTaskDelete(NULL);
}