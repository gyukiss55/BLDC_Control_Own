// ChatGPT: write a code snippet for blackpill using Arduino ide and stm32f4xx_hal.h for handling 6 PWM output with syncronized common period

#include "Arduino.h"

#include "stm32f4xx_hal.h"

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;

void SystemClock_Config(void);
void MX_TIM3_Init(void);
void MX_TIM5_Init(void);

int dutyCycle = 0; // Start at 0% duty cycle
int increment = 1; // Increment step for the duty cycle

void setup() {
    // Initialize HAL and system clock
    HAL_Init();
    SystemClock_Config();

    // Initialize the timers
    MX_TIM3_Init();
    MX_TIM5_Init();

    // Start PWM for TIM5 (PA0, PA1, PA2, PA3)
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);

    // Start PWM for TIM3 (PA6, PA7)
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void loop() {
    // Update the PWM duty cycle on all channels
    setPWM_DutyCycle(dutyCycle);

    // Increment or decrement duty cycle
    dutyCycle += increment;
    if (dutyCycle >= 100 || dutyCycle <= 0) {
        increment = -increment; // Reverse the direction
    }

    // Add delay to slow the transition
    HAL_Delay(10);
}

void setPWM_DutyCycle(int percentage) {
    // Calculate pulse based on percentage (TIM Period is 999 for 1 kHz frequency)
    int pulse = (percentage * 999) / 100;

    // Set PWM duty cycle for TIM5 (PA0, PA1, PA2, PA3)
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, pulse); // PA0
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, pulse); // PA1
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, pulse); // PA2
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, pulse); // PA3

    // Set PWM duty cycle for TIM3 (PA6, PA7)
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse); // PA6
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse); // PA7
}

void MX_TIM5_Init(void) {
    __HAL_RCC_TIM5_CLK_ENABLE();

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 84 - 1; // 1 MHz timer clock (84 MHz / 84)
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 999; // 1 kHz PWM frequency
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_PWM_Init(&htim5); // Initialize TIM5 for PWM

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.Pulse = 0; // Start with 0% duty cycle

    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4);
}

void MX_TIM3_Init(void) {
    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 84 - 1; // 1 MHz timer clock (84 MHz / 84)
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 999; // 1 kHz PWM frequency
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_PWM_Init(&htim3); // Initialize TIM3 for PWM

    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.Pulse = 0; // Start with 0% duty cycle

    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    // Initialize PLL and system clock to 84 MHz
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    // Configure the system clock
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
