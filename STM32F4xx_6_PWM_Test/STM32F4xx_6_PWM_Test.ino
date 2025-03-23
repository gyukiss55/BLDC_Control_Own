void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("PWM a8, A9, A10, A0, A6, A7 (50, 30, 70, 20, 80, 60)");

  LED_Init();

  // Timer initialization
  pwmInit();
}

void LED_Init()
{
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);

}

void loop() {
  // Change duty cycles dynamically (example: sweep)
  setPWMDuty(TIM1, 1, 50); // TIM1 CH1 = PA8
  setPWMDuty(TIM1, 2, 30); // TIM1 CH2 = PA9
  setPWMDuty(TIM1, 3, 70); // TIM1 CH3 = PA10

  setPWMDuty(TIM2, 1, 20); // TIM2 CH1 = PA0
  setPWMDuty(TIM3, 1, 80); // TIM3 CH1 = PA6
  setPWMDuty(TIM3, 2, 60); // TIM3 CH2 = PA7

  LED_Toggle();
  Serial.print(millis());
  Serial.println(" PWM a8, A9, A10, A0, A6, A7 (50, 30, 70, 20, 80, 60)");
  LED_Toggle();
}

void LED_Toggle()
{
  digitalWrite(PC13, HIGH);
  delay(800);
  digitalWrite(PC13, LOW);
  delay(200);

}


void pwmInit() {
  // Enable clocks
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN;

  // Set up PWM frequency = 100kHz (Period = 10 µs)
  // Assuming 84 MHz clock
  const uint16_t prescaler = 0;
  const uint16_t period = 839; // 84MHz / (prescaler+1) / (period+1) = 100 kHz

  setupTimerPWM(TIM1, prescaler, period, 3); // 3 channels
  setupTimerPWM(TIM2, prescaler, period, 1); // 1 channel
  setupTimerPWM(TIM3, prescaler, period, 2); // 2 channels

  // GPIO setup
  
  pinMode(PA8, LL_GPIO_OUTPUT_PUSHPULL);
  pinMode(PA9, LL_GPIO_OUTPUT_PUSHPULL);
  pinMode(PA10, LL_GPIO_OUTPUT_PUSHPULL);
  pinMode(PA0, LL_GPIO_OUTPUT_PUSHPULL);
  pinMode(PA6, LL_GPIO_OUTPUT_PUSHPULL);
  pinMode(PA7, LL_GPIO_OUTPUT_PUSHPULL);
  
}

void setupTimerPWM(TIM_TypeDef* TIMx, uint16_t prescaler, uint16_t period, uint8_t channels) {
  TIMx->PSC = prescaler;
  TIMx->ARR = period;
  TIMx->CR1 |= TIM_CR1_ARPE;

  if (channels >= 1) {
    TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // PWM mode 1
    TIMx->CCMR1 |= TIM_CCMR1_OC1PE;
    TIMx->CCER |= TIM_CCER_CC1E;
  }
  if (channels >= 2) {
    TIMx->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    TIMx->CCMR1 |= TIM_CCMR1_OC2PE;
    TIMx->CCER |= TIM_CCER_CC2E;
  }
  if (channels >= 3) {
    TIMx->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
    TIMx->CCMR2 |= TIM_CCMR2_OC3PE;
    TIMx->CCER |= TIM_CCER_CC3E;
  }

  TIMx->EGR |= TIM_EGR_UG;
  TIMx->CR1 |= TIM_CR1_CEN;
}

void setPWMDuty(TIM_TypeDef* TIMx, uint8_t channel, uint8_t duty_percent) {
  uint16_t value = (TIMx->ARR * duty_percent) / 100;
  switch (channel) {
    case 1: TIMx->CCR1 = value; break;
    case 2: TIMx->CCR2 = value; break;
    case 3: TIMx->CCR3 = value; break;
    case 4: TIMx->CCR4 = value; break;
  }
}
