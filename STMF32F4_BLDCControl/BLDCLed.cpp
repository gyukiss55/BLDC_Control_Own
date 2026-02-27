// BLDCLed.cpp
#include "BLDCLed.h"
void setupBLDCLed()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void BlinkLed()
{
  static uint32_t lastTS = 0;
  static bool state = false; 
  uint32_t nowTS = millis(); 
  if (nowTS - lastTS > 1000) {
	lastTS += 1000;
	state = !state;
	digitalWrite(LED_BUILTIN, state?HIGH:LOW);
  }
}
