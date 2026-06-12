// TimerTrigger.cpp
#include "Arduino.h"
#include "TimerTrigger.h"


TimerTrigger::TimerTrigger() {
  
}

void TimerTrigger::begin(uint32_t interval, uint32_t counter) {
	if (interval == 0) {
		state = TIMER_OFF;
	}
	else {
		timerInterval = interval;
		timerCounter = counter;
		triggerCounter = 0;
		lastTriggerTime = millis();
		state = IDLE;
	}
}

bool TimerTrigger::checkAndStep()
{
	if (state == TIMER_OFF) {
		return false; // Timer is off, do nothing
	}
	if (state == IDLE) {
		uint32_t currentTime = millis();
		if (currentTime - lastTriggerTime >= timerInterval) {
			triggerCounter++;
			lastTriggerTime += timerInterval; // Update the last trigger time
			if (timerCounter == 0) {
				state = IDLE; // Set state back to idle
			}
			else if (timerCounter > triggerCounter) {
				state = IDLE; // Set state back to idle
			}
			else {
				state = TIMER_OFF; // No more triggers, turn off the timer
			}
			return true; // Timer triggered
		}
	}
	return false; // Timer not triggered
}
