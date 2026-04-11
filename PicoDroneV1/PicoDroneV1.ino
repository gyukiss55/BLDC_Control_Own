/*************************************************** 
  This is a library for the PicoDrone
 ****************************************************/

#include <Arduino.h>
#include "PicoDroneSerial.h"
#include "PicoDronePWM.h"
#include "PicoDroneWeb.h"
#include "PicoDroneGAM.h"
#include "PicoDroneGPS.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("PicoDrone V0.1 setup start");
  PicoDroneSerial_init();
  PicoDronePWM_init();
  PicoDroneGAM_init();
  PicoDroneGPS_init();
  PicoDroneWeb_init();
  Serial.println("PicoDrone V0.1 setup end");
}

void loop() {
  PicoDroneSerial_loop();
  PicoDroneGPS_update();
  PicoDroneGAM_update(false);
  PicoDroneWeb_loop();
}
