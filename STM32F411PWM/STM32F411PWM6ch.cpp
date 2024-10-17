#include "Arduino.h"
#include <HardwareTimer.h>
#include "STM32F411PWM6ch.h"

// Define the pins for PWM output
#define PWM_PIN_1 PA0 // Timer 2 Channel 1
#define PWM_PIN_2 PA1 // Timer 2 Channel 2
#define PWM_PIN_3 PA2 // Timer 2 Channel 3
#define PWM_PIN_4 PA3 // Timer 2 Channel 4
#define PWM_PIN_5 PB6 // Timer 4 Channel 1
#define PWM_PIN_6 PB7 // Timer 4 Channel 2

// Create hardware timer objects
HardwareTimer *Timer2 = new HardwareTimer(TIM2);
HardwareTimer *Timer4 = new HardwareTimer(TIM4);

void setupSTM32F411PWM6ch() {
  // Set PWM pins as output
  pinMode(PWM_PIN_1, PWM);
  pinMode(PWM_PIN_2, PWM);
  pinMode(PWM_PIN_3, PWM);
  pinMode(PWM_PIN_4, PWM);
  pinMode(PWM_PIN_5, PWM);
  pinMode(PWM_PIN_6, PWM);

  // Configure Timer 2 for 4 PWM channels
  Timer2->setOverflow(1000000, HERTZ); // Set the frequency to 1 MHz
  Timer2->setPWM(PWM_PIN_1, 128);      // Set duty cycle to 50% (128/255)
  Timer2->setPWM(PWM_PIN_2, 128);      // Set duty cycle to 50% (128/255)
  Timer2->setPWM(PWM_PIN_3, 128);      // Set duty cycle to 50% (128/255)
  Timer2->setPWM(PWM_PIN_4, 128);      // Set duty cycle to 50% (128/255)

  // Configure Timer 4 for 2 PWM channels
  Timer4->setOverflow(1000000, HERTZ); // Set the frequency to 1 MHz
  Timer4->setPWM(PWM_PIN_5, 128);      // Set duty cycle to 50% (128/255)
  Timer4->setPWM(PWM_PIN_6, 128);      // Set duty cycle to 50% (128/255)

  // Start the timers
  Timer2->resume();
  Timer4->resume();
}

void loopSTM32F411PWM6ch() {
  // You can change the duty cycle dynamically here if needed
  // Timer2->setCaptureCompare(PWM_PIN_1, newDutyCycle, PERCENT_COMPARE_FORMAT);
}
