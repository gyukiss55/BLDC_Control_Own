
#include <Arduino.h>
#include "DigiInput.h"

void setup()
{
	Serial.begin(115200);
	delay(2000);
	setupDigiInput();
	Serial.println("ESP32 Digi Scope");
}

void loop()
{
	loopDigiInput();

}