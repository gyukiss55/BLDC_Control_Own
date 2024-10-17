#include "Arduino.h"
#include "stm32f4xx_hal.h"
#include "STM32F411PWM6chv2.h"


// Pin Definitions (you may need to adjust based on your board)
#define PWM_PIN1 PA8  // TIM1_CH1
#define PWM_PIN2 PA9  // TIM1_CH2
#define PWM_PIN3 PA10 // TIM1_CH3
#define PWM_PIN4 PA5  // TIM2_CH1
#define PWM_PIN5 PA6  // TIM3_CH1
#define PWM_PIN6 PA7  // TIM3_CH2

// Timer Handles
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

// PWM Configuration: 1 MHz frequency, 256 steps (8-bit resolution)
const uint32_t PWM_FREQUENCY = 1000000; // 1 MHz
const uint32_t TIMER_CLOCK = 100000000; // 100 MHz, assuming max clock
const uint32_t PRESCALER = 0;           // No prescaler (TIM clock = system clock)
const uint32_t PERIOD = 255;            // 256 steps for duty cycle (8-bit resolution)

// Function prototypes
void initPWM(TIM_HandleTypeDef* htim, TIM_TypeDef* TIMx, uint32_t Channel, uint32_t Pin);
void setPWMDutyCycle(TIM_HandleTypeDef* htim, uint32_t Channel, uint8_t dutyCycle);

void setupSTM32F411PWM6chv2() {
  // Initialize HAL Library
  HAL_Init();

  // Initialize PWM outputs on 6 pins
  initPWM(&htim1, TIM1, TIM_CHANNEL_1, PWM_PIN1);
  initPWM(&htim1, TIM1, TIM_CHANNEL_2, PWM_PIN2);
  initPWM(&htim1, TIM1, TIM_CHANNEL_3, PWM_PIN3);
  
  initPWM(&htim2, TIM2, TIM_CHANNEL_1, PWM_PIN4);
  initPWM(&htim3, TIM3, TIM_CHANNEL_1, PWM_PIN5);
  initPWM(&htim3, TIM3, TIM_CHANNEL_2, PWM_PIN6);

  // Start PWM with some initial duty cycle (50%)
  setPWMDutyCycle(&htim1, TIM_CHANNEL_1, 128); // 50% duty cycle
  setPWMDutyCycle(&htim1, TIM_CHANNEL_2, 128);
  setPWMDutyCycle(&htim1, TIM_CHANNEL_3, 128);

  setPWMDutyCycle(&htim2, TIM_CHANNEL_1, 128);
  setPWMDutyCycle(&htim3, TIM_CHANNEL_1, 128);
  setPWMDutyCycle(&htim3, TIM_CHANNEL_2, 128);
}

void loopSTM32F411PWM6chv2() {
  // In loop, you can change the duty cycle dynamically if needed
}

// Function to initialize a PWM output
void initPWMSTM32F411PWM6chv2(TIM_HandleTypeDef* htim, TIM_TypeDef* TIMx, uint32_t Channel, uint32_t Pin) {
  // Configure GPIO Pin for PWM output
  pinMode(Pin, OUTPUT_AF_PP); // Alternate function push-pull

  // Configure the timer for PWM generation
  htim->Instance = TIMx;
  htim->Init.Prescaler = PRESCALER;
  htim->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim->Init.Period = PERIOD; // 8-bit resolution (256 steps)
  htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim->Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(htim);

  // Configure PWM channel
  TIM_OC_InitTypeDef sConfigOC = {0};
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0; // Initial duty cycle (0%)
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, Channel);

  // Start PWM channel
  HAL_TIM_PWM_Start(htim, Channel);
}

// Function to set the PWM duty cycle (0-255 range for 8-bit resolution)
void setPWMDutyCycleSTM32F411PWM6chv2(TIM_HandleTypeDef* htim, uint32_t Channel, uint8_t dutyCycle) {
  __HAL_TIM_SET_COMPARE(htim, Channel, dutyCycle); // Set duty cycle
}
