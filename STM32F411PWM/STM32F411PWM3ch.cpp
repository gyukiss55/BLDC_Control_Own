#include "Arduino.h"
#include "stm32f4xx_hal.h"
#include "STM32F411PWM3ch.h"

// Define the output pins
#define PWM_PIN_1 PA8  // Timer 1, Channel 1
#define PWM_PIN_2 PA9  // Timer 1, Channel 2
#define PWM_PIN_3 PA10 // Timer 1, Channel 3

void setupSTM32F411PWM3ch() {
  // Initialize each pin as an output for PWM
  pinMode(PWM_PIN_1, OUTPUT);
  pinMode(PWM_PIN_2, OUTPUT);
  pinMode(PWM_PIN_3, OUTPUT);

  // Start the hardware timers for 1MHz PWM frequency
  pwmInitSTM32F411PWM3ch();
}

void pwmInitSTM32F411PWM3ch() {
  // Initialize Timer 1
  TIM_HandleTypeDef TimHandle;
  TIM_OC_InitTypeDef sConfigOC;
  
  __HAL_RCC_TIM1_CLK_ENABLE(); // Enable clock for Timer 1

  // Timer configuration
  TimHandle.Instance = TIM1;
  TimHandle.Init.Prescaler = (SystemCoreClock / 1000000) - 1; // Set prescaler for 1 MHz base frequency
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.Period = 255; // Set ARR for 256-step duty cycle (0 to 255)
  TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TimHandle.Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(&TimHandle);

  // PWM Mode configuration
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 128; // 50% duty cycle initially
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  // Set PWM on Channel 1 (PA8)
  HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);

  // Set PWM on Channel 2 (PA9)
  HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);

  // Set PWM on Channel 3 (PA10)
  HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfigOC, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);
}

void setDutyCycleSTM32F411PWM3ch(uint8_t duty1, uint8_t duty2, uint8_t duty3) {
  // Change the duty cycle on each channel
  __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_1, duty1);
  __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_2, duty2);
  __HAL_TIM_SET_COMPARE(&TimHandle, TIM_CHANNEL_3, duty3);
}

void loopSTM32F411PWM3ch() {
  // Example usage: Change duty cycle over time
  for (uint8_t i = 0; i <= 255; i++) {
    setDutyCycleSTM32F411PWM3ch(i, 255 - i, i / 2);  // Adjust PWM duty cycle dynamically
    delay(10);  // Delay to see effect
  }
}
