
#include "Arduino.h"
#include "STM32F411PWM6chv3.h"
#include "MilliSecDelay.h"
#include "ESCControl.h"

#if defined (_STM32F411PWM6CHV3_)
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

#endif // _STM32F411PWM6CHV3_
//-------------------------------------------------------------------
// Define the PWM pins
//#define PWM_PIN1 PB12
//#define PWM_PIN2 PB13
//#define PWM_PIN3 PB14
//#define PWM_PIN4 PB15
//#define PWM_PIN5 PB8
//#define PWM_PIN6 PB9

#define PWM_PINAH PB12
#define PWM_PINAL PB13
#define PWM_PINBH PB14
#define PWM_PINBL PB15
#define PWM_PINCH PB8
#define PWM_PINCL PB9

// Desired frequency and resolution
const uint32_t pwm_frequency = 100000; // 100 kHz
const uint8_t pwm_resolution = 255;     // 8-bit resolution (0-255)

uint8_t speed = 0;

HardwareTimer *timerPWM = new HardwareTimer(TIM4); // for PB7

// Setup function
void setupPWM3V1() {
    // Set the PWM frequency for each pin
    /*
    analogWriteFrequency(PWM_PIN1, pwm_frequency);
    analogWriteFrequency(PWM_PIN2, pwm_frequency);
    analogWriteFrequency(PWM_PIN3, pwm_frequency);

    // Set initial duty cycles
    analogWrite(PWM_PIN1, 128);  // 50% duty cycle
    analogWrite(PWM_PIN2, 64);   // 25% duty cycle
    analogWrite(PWM_PIN3, 192);  // 75% duty cycle
    */

    // Automatically retrieve TIM instance and channel associated to pin
  // This is used to be compatible with all STM32 series automatically.
  // 
  //TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PWM_PIN1), PinMap_PWM);
  //uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PWM_PIN1), PinMap_PWM));


  // Instantiate HardwareTimer object. Thanks to 'new' instantiation, HardwareTimer is not destructed when setup() function is finished.
  //HardwareTimer *MyTim = new HardwareTimer(Instance);

  // Configure and start PWM
  // MyTim->setPWM(channel, pin, 5, 10, NULL, NULL); // No callback required, we can simplify the function call
  //MyTim->setPWM(channel, PWM_PIN1, 5, 10); // 5 Hertz, 10% dutycycle

  // Assuming Ax pins have PWM capabilities and use a different Timer.

    uint32_t pwm_freq = 100000; // 100 kHz
    uint32_t pwm_period = (SystemCoreClock / pwm_freq) - 1; // AutoReload érték

  // timerPWM->setPWM(PWM_PIN1, STM_PIN_CHANNEL(2), pwm_freq, 128);
    speed = 0;
/*
    analogWriteFrequency(2000); // Set PWM period to 2 kHz instead of 1000
    analogWrite(PWM_PIN4, speed); // Start PWM on A4
    analogWrite(PWM_PIN1, speed); // Start PWM on A1
    analogWrite(PWM_PIN2, speed); // Start PWM on A2
    analogWrite(PWM_PIN3, speed); // Start PWM on A3
    analogWrite(PWM_PIN5, speed); // Start PWM on A5
    analogWrite(PWM_PIN6, speed); // Start PWM on A6
*/
    delay(1000);
}

void SetDuty(int pwm_pin, int duty) {
  timerPWM->setCaptureCompare(STM_PIN_CHANNEL(2), duty);
}

// Main loop
void loopPWM3V1()
{
    int stepTime = 10; // ms
    for (int8_t s = 0; s <= 255; s++) {
        speed = s;
        //SetDuty(PWM_PIN1, speed);
        /*
        for (int8_t f = 0; f <= 5; f++) {
            analogWrite(PWM_PIN1, 0); 
            analogWrite(PWM_PIN2, 0); 
            analogWrite(PWM_PIN3, 0); 
            analogWrite(PWM_PIN4, 0); 
            analogWrite(PWM_PIN5, 0); 
            analogWrite(PWM_PIN6, 0); 

            //MicroSecDelay delMicrosSec;
            //delMicrosSec.Restart(10000);

            //while (!delMicrosSec.TestAndSet()) {}

            switch (f) {
            case 0:
                analogWrite(PWM_PIN1, speed); 
                analogWrite(PWM_PIN4, speed); 
                break;
            case 1:
                analogWrite(PWM_PIN5, speed);
                analogWrite(PWM_PIN4, speed);
                break;
            case 2:
                analogWrite(PWM_PIN5, speed);
                analogWrite(PWM_PIN2, speed);
                break;
            case 3:
                analogWrite(PWM_PIN3, speed);
                analogWrite(PWM_PIN2, speed);
                break;
            case 4:
                analogWrite(PWM_PIN3, speed);
                analogWrite(PWM_PIN6, speed);
                break;
            case 5:
                analogWrite(PWM_PIN1, speed);
                analogWrite(PWM_PIN6, speed);
                break;
            }
            delay(stepTime);
        }
        */

    }

}

const int numPhases = 6;
const int baseCycleTime = 100000;

static uint32_t lastUpdateTime = 0;
static uint32_t lastPulseTime = 0;
static int currentPhase = 0;

static int cycleTime = baseCycleTime; // 100 ms cycle time for 6-step commutation (adjust as needed)
static int currentPeriodTime = 0;
static int currentPulseTime = 0;

void ClearAllPWMPin()
{
    digitalWrite(PWM_PINAH, LOW);
    digitalWrite(PWM_PINAL, LOW);
    digitalWrite(PWM_PINBH, LOW);
    digitalWrite(PWM_PINBL, LOW);
    digitalWrite(PWM_PINCH, LOW);
    digitalWrite(PWM_PINCL, LOW);
}

// Setup function
void setupPWM6V1() {
	pinMode(PWM_PINAH, OUTPUT);
    pinMode(PWM_PINAL, OUTPUT);
    pinMode(PWM_PINBH, OUTPUT);
    pinMode(PWM_PINBL, OUTPUT);
    pinMode(PWM_PINCH, OUTPUT);
    pinMode(PWM_PINCL, OUTPUT);

    ClearAllPWMPin();

    currentPeriodTime = GetNextPeriod();
    currentPulseTime = GetNextPulse();

	lastUpdateTime = micros() + 10*1000*1000;
}

void loopPWM6V1() {
    uint32_t now = micros();
    if (now < lastUpdateTime) {
        lastUpdateTime = now;
        return;
    }
	bool updatePhase = false;
    if (now - lastUpdateTime > currentPeriodTime) {
        lastUpdateTime += currentPeriodTime;
		lastPulseTime = lastUpdateTime + currentPulseTime;
        currentPhase = (currentPhase + 1) % numPhases;
        currentPeriodTime = GetNextPeriod();
        currentPulseTime = GetNextPulse();
        ClearAllPWMPin();
		updatePhase = true;
	}
    if (currentPulseTime > 0 && currentPulseTime < currentPeriodTime) {
        if (updatePhase) {
            switch (currentPhase) {
            case 0:
                digitalWrite(PWM_PINAH, HIGH);
                digitalWrite(PWM_PINBL, HIGH);
                break;
            case 1:
                digitalWrite(PWM_PINAL, HIGH);
                digitalWrite(PWM_PINBL, HIGH);
                break;
            case 2:
                digitalWrite(PWM_PINAL, HIGH);
                digitalWrite(PWM_PINCH, HIGH);
                break;
            case 3:
                digitalWrite(PWM_PINBH, HIGH);
                digitalWrite(PWM_PINCH, HIGH);
                break;
            case 4:
                digitalWrite(PWM_PINBH, HIGH);
                digitalWrite(PWM_PINCL, HIGH);
                break;
            case 5:
                digitalWrite(PWM_PINAH, HIGH);
                digitalWrite(PWM_PINCL, HIGH);
                break;
            }
            updatePhase = false;
		}
        if (now > lastPulseTime) {
            ClearAllPWMPin();
		}
    }

}
