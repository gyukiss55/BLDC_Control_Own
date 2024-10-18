// ChatGPT: write a code snippet for blackpill using Arduino ide and stm32f4xx_hal.h for handling 6 PWM output with syncronized common period

#include "Arduino.h"

#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

void SystemClock_Config(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

int dutyCycle = 0; // Starting duty cycle at 0%
int increment = 1; // Increment by 1% each time

void setup() {
  // Initialize the HAL Library
  HAL_Init();
  
  // Configure the system clock
  SystemClock_Config();
  
  // Initialize Timer 2 and Timer 3 for PWM
  MX_TIM2_Init();
  MX_TIM3_Init();

  // Start PWM on Timer 2, Channels 1 and 2
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  
  // Start PWM on Timer 3, Channels 1, 2, 3, and 4
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
}

void loop() {
  // Update all PWM channels with the current duty cycle
  setPWM_DutyCycle(dutyCycle);

  // Increment or decrement duty cycle
  dutyCycle += increment;

  // If duty cycle reaches 100%, start decrementing
  if (dutyCycle >= 100) {
    increment = -1; // Start decrementing
  }
  
  // If duty cycle reaches 0%, start incrementing
  if (dutyCycle <= 0) {
    increment = 1; // Start incrementing
  }
  
  // Add some delay to see smooth transitions (adjust as needed)
  HAL_Delay(10); // 10ms delay
}

// Function to set the PWM duty cycle for all 6 channels
void setPWM_DutyCycle(int percentage) {
  // Calculate the pulse value based on percentage
  int pulse = (percentage * 999) / 100;

  // Update PWM duty cycle for Timer 2, Channel 1 (10%)
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pulse * 1 / 10);

  // Update PWM duty cycle for Timer 2, Channel 2 (20%)
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse * 2 / 10);
  
  // Update PWM duty cycle for Timer 3, Channel 1 (30%)
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse * 3 / 10);
  
  // Update PWM duty cycle for Timer 3, Channel 2 (40%)
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse * 4 / 10);

  // Update PWM duty cycle for Timer 3, Channel 3 (50%)
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse * 5 / 10);

  // Update PWM duty cycle for Timer 3, Channel 4 (60%)
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pulse * 6 / 10);
}

void MX_TIM2_Init(void) {
  __HAL_RCC_TIM2_CLK_ENABLE(); // Enable Timer 2 clock
  
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 84 - 1; // 1 MHz timer clock (84 MHz system clock)
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;       // 1 kHz PWM frequency (1 MHz / 1000)
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  HAL_TIM_PWM_Init(&htim2); // Initialize PWM for TIM2
  
  TIM_OC_InitTypeDef sConfigOC;
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  // Configure PWM for TIM2 Channel 1 and 2
  sConfigOC.Pulse = 0; // Start with 0% duty cycle
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
}

void MX_TIM3_Init(void) {
  __HAL_RCC_TIM3_CLK_ENABLE(); // Enable Timer 3 clock
  
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 84 - 1; // 1 MHz timer clock (84 MHz system clock)
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;       // 1 kHz PWM frequency
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  HAL_TIM_PWM_Init(&htim3); // Initialize PWM for TIM3
  
  TIM_OC_InitTypeDef sConfigOC;
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  // Configure PWM for TIM3 Channel 1, 2, 3, and 4
  sConfigOC.Pulse = 0; // Start with 0% duty cycle
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4);
}

// Configure the system clock to 84 MHz
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  // Enable HSE Oscillator and activate PLL
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // Configure the system clock source and dividers
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
