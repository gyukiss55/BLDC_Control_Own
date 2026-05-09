
#include <Arduino.h>

#include "WireCustom.h"

#include "BMP280_PressureSensor.h"
#include "MPU6500_WESensor.h"
#include "QMC5883LCompassSensor.h"


void setup() {
  Serial.begin(115200);
  delay(2000);
  setupWire ();

  scanWire();

  Serial.println("Sensor setup start");
  setupBMP280PressureSensor();
  Serial.println("BMP280_PressureSensor setup complete");	
  setupMPU6500_WESensor();
  Serial.println("MPU6500_WESensor setup complete");
  //setupQMC5883LCompass();
  Serial.println("QMC5883LCompass setup complete");
  
}

void loop() {
  loopBMP280PressureSensor();
  loopMPU6500_WESensor();
//  loopQMC5883LCompass();

  delay(1000);
}
