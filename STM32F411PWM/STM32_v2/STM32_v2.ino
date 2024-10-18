#include "stm32f4xx_hal.h"

// Define PWM frequency and resolution
#define PWM_FREQUENCY 1000000 // 1 MHz
#define PWM_RESOLUTION 256     // 8-bit resolution

// Define PWM pins
#define PWM_PIN_1 GPIO_PIN_6   // PA6
#define PWM_PIN_2 GPIO_PIN_7   // PA7
#define PWM_PIN_3 GPIO_PIN_0   // PA0
#define PWM_PIN_4 GPIO_PIN_1   // PA1
#define PWM_PIN_5 GPIO_PIN_2   // PA2
#define PWM_PIN_6 GPIO_PIN_3   // PA3

#define LED_PIN PC13

// Timer handles
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM3_Init(void);
void MX_TIM5_Init(void);

void setup() {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_TIM5_Init();

    // Start PWM on all channels
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // PA6
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // PA7
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1); // PA0
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2); // PA1
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3); // PA2
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4); // PA3

    // Set initial duty cycle to 0 (off)
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 0);
	
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	digitalWrite(LED_PIN, HIGH);
    for (int dutyCycle = 0; dutyCycle < PWM_RESOLUTION; dutyCycle++) {
        uint32_t compareValue = (dutyCycle * (htim3.Init.Period + 1)) / PWM_RESOLUTION;
        
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, compareValue);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, compareValue);
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, compareValue);
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, compareValue);
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, compareValue);
        __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, compareValue);

        HAL_Delay(10); // Adjust delay as needed for testing purposes
    }
	digitalWrite(LED_PIN, LOW);
	HAL_Delay(1000); 
}

// Timer initialization functions
void MX_TIM3_Init(void) {
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = (SystemCoreClock / (PWM_FREQUENCY * (PWM_RESOLUTION + 1))) - 1;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = PWM_RESOLUTION - 1;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim3);

    TIM_OC_InitTypeDef sConfigOC;
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0; 
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
}

void MX_TIM5_Init(void) {
    htim5.Instance = TIM5;
    htim5.Init.Prescaler = (SystemCoreClock / (PWM_FREQUENCY * (PWM_RESOLUTION + 1))) - 1;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = PWM_RESOLUTION - 1;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim5);

    TIM_OC_InitTypeDef sConfigOC;

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0; 
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4);
}

void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = PWM_PIN_1 | PWM_PIN_2 | PWM_PIN_3 | PWM_PIN_4 | PWM_PIN_5 | PWM_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; 
    GPIO_InitStruct.Pull = GPIO_NOPULL; 
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; 
   
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void SystemClock_Config(void) {
   // Configure the system clock as needed for your application.
}
