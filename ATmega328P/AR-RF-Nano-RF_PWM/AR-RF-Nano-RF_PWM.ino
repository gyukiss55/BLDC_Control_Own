#include <Arduino.h>
#include "pwmOutput.h"
#include "MeasureInput.h"


void setup ()
{
	Serial.begin(115200);
	delay(2000);
	setupPWMOutput();
	setupMeasureInput();
}

void loop ()
{
	loopPWMOutput();
	loopMeasureInput();
}
