// TimerTrigger.h

#ifndef TIMERTRIGGER_H
#define TIMERTRIGGER_H

#include "Arduino.h"

class TimerTrigger {
public:
	enum TimerState { TIMER_OFF, IDLE, TRIGGERED } timerState = IDLE; // State of the timer
	//	enum TimerMode { ONE_SHOT, PERIODIC } timerMode = PERIODIC; // Mode of the timer
private:
	uint32_t timerInterval = 0; // Timer interval in milliseconds
	uint32_t lastTriggerTime = 0; // Last time the timer was triggered	
	uint32_t timerCounter = 0; // Counter to keep track of timer triggers
	uint32_t triggerCounter = 0; // Counter to keep track of timer triggers
	TimerState state = TIMER_OFF; // Current state of the timer
	//	TimerMode mode = ONE_SHOT; // Current state of the timer
public:
	TimerTrigger();
	void begin(uint32_t interval = 0, uint32_t counter = 0);
	bool checkAndStep();
	TimerState getState() const { return state; }
	uint32_t getCounter() const { return timerCounter; }
	uint32_t getTriggerCounter() const { return triggerCounter; }
};

#endif
