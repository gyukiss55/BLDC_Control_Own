#include "Arduino.h"
#include "stm32f4xx_hal.h"
#include "STM32F411PWM6chv3.h"


// Pin Definitions (you may need to adjust based on your board)
#define TIM1_CH1 PB8 
#define TIM1_CH2 PB9 
#define TIM1_CH3 PB12
#define TIM1_CH4 PB13
#define TIM1_CH5 PB14
#define TIM1_CH6 PB15

// Function prototypes

// Global variables for timer handle and PWM configuration
TIM_HandleTypeDef htim1;

void setupSTM32F411PWM6chv3() {
    // Initialize the HAL library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize GPIOs for PWM output
    GPIO_InitSTM32F411PWM6chv3();

    // Initialize Timer1 for PWM generation
    TIM1_PWM_InitSTM32F411PWM6chv3();

    // Start PWM on all 6 channels
    HAL_TIM_PWM_Start(&htim1, TIM1_CH1); // PB8
    HAL_TIM_PWM_Start(&htim1, TIM1_CH2); // PB9
    HAL_TIM_PWM_Start(&htim1, TIM1_CH3); // PB12
    HAL_TIM_PWM_Start(&htim1, TIM1_CH4); // PB13

    // Use complementary channels for PB14, PB15
    HAL_TIM_PWM_Start(&htim1, TIM1_CH5); // PB14
    HAL_TIM_PWM_Start(&htim1, TIM1_CH6); // PB15
}

void loopSTM32F411PWM6chv3() {
    // Example: Adjust duty cycles dynamically
    for (int dutyCycle = 0; dutyCycle < 256; dutyCycle++) {
        for (int state = 0; state < 6; state++) {
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH1, 0);  // PB8
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH2, 0);  // PB9
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH3, 0);  // PB12
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH4, 0);  // PB13
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH5, 0);  // PB14
            __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH6, 0);  // PB15
            switch (state) {
            case 0:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH1, dutyCycle);  // PB8
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH4, dutyCycle);  // PB13
                break;
            case 1:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH4, dutyCycle);  // PB13
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH5, dutyCycle);  // PB14
                break;
            case 2:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH5, dutyCycle);  // PB14
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH2, dutyCycle);  // PB9
                break;
            case 3:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH2, dutyCycle);  // PB9
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH3, dutyCycle);  // PB12
                break;
            case 4:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH3, dutyCycle);  // PB12
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH6, dutyCycle);  // PB15
                break;
            case 5:
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH6, dutyCycle);  // PB15
                __HAL_TIM_SET_COMPARE(&htim1, TIM1_CH1, dutyCycle);  // PB8
                break;
            }
            HAL_Delay(10);

        }
    }
}

// Timer 1 PWM Initialization
void TIM1_PWM_InitSTM32F411PWM6chv3(void) {
    TIM_OC_InitTypeDef sConfigOC = { 0 };

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 1 - 1;  // Prescaler = 0 for 1 MHz frequency
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 255;  // 256 resolution (ARR = 255)
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
        // Initialization error
        while (1);
    }

    // Configure PWM for all channels
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;  // Initial duty cycle = 0%
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // PWM on channels 1, 2, 3, 4
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH1);  // PB8
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH2);  // PB9
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH3);  // PB12
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH4);  // PB13
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH5);  // PB14
    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM1_CH6);  // PB15

    // PWM on complementary channels 1N, 2N
}

// GPIO Initialization for PWM pins
void GPIO_InitSTM32F411PWM6chv3(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();  // Enable GPIOB clock

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    // Configure PB8, PB9, PB12, PB13, PB14, PB15 as Alternate Function for TIM1
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Alternate function, push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// System Clock Configuration (100 MHz HCLK)
void SystemClock_ConfigSTM32F411PWM6chv3(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    // Configure the main internal regulator output voltage
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // Initialize the HSE Oscillator and configure the PLL to reach 100 MHz
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 200;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        // Initialization Error
        while (1);
    }

    // Initialize the CPU, AHB, and APB buses clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        // Initialization Error
        while (1);
    }
}
