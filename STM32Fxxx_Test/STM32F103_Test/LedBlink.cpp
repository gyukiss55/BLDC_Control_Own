// LedBlink.cpp
#include "Arduino.h"
#include "LedBlink.h"
#include "TimerTrigger.h"

#define LED_BUILTIN1 PC13
#define LED_HALFPERIOD 500

TimerTrigger ledTimer;

void LedBlink_Init()
{
	pinMode(LED_BUILTIN1, OUTPUT);
	ledTimer.begin(LED_HALFPERIOD, 0);
}

void LedBlink_Toggle() {

	if (ledTimer.checkAndStep()) {
		digitalWrite(LED_BUILTIN1, (ledTimer.getTriggerCounter() % 2) == 0? HIGH : LOW);  // set the LED to the new state
		//Serial.println(ledTimer.getTriggerCounter());
	}
}
