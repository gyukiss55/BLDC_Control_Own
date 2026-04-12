/*************************************************** 
  This is a library for the PicoDrone
 ****************************************************/

#include <Arduino.h>
#include "PicoDroneSerial.h"
#include "PicoDronePWM.h"
#include "PicoDroneWeb.h"
#include "PicoDroneWire.h"
#include "PicoDroneMPU6500.h"
#include "PicoDroneBMP280.h"
#include "PicoDroneGPS.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("PicoDrone V0.1 setup start");
  PicoDroneSerial_init();
  PicoDronePWM_init();

  PicoDroneWire_init();
  PicoDroneMPU6500_init();
  PicoDroneBMP280_init();

  PicoDroneGPS_init();
  PicoDroneWeb_init();
  Serial.println("PicoDrone V0.1 setup end");
}

void loop() {
  PicoDroneSerial_loop();
  PicoDroneGPS_update();
  PicoDroneMPU6500_update(false);
  PicoDroneBMP280_update(false);
  PicoDroneWeb_loop();
}
