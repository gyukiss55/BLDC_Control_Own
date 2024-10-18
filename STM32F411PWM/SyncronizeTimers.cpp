// ChatGPT : how many pwm pin can be controlled by STM32F411
// ChatGPT : how can I start 2 timers at the same time in stm32f411
// 
// Declare Timer Handles
TIM_HandleTypeDef htim1;  // Master Timer
e:\Work\GitHub\_MyGit\BLDC_Control_Own\STM32F411PWM\STM32F411PWM\STM32F411PWM.inoTIM_HandleTypeDef htim2;  // Slave Timer

// Master Timer (TIM1) configuration
void MX_TIM1_Init(void)
{
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1000;  // Example period
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim1);

  // Set TIM1 as master
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);
}

// Slave Timer (TIM2) configuration
void MX_TIM2_Init(void)
{
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000;  // Example period
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  // Set TIM2 to trigger on TIM1
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0; // Use ITR0 (TIM1 as master)
  HAL_TIM_SlaveConfigSynchronization(&htim2, &sSlaveConfig);
}

// Start both timers
void Start_Timers(void)
{
  HAL_TIM_Base_Start(&htim1);  // Start master timer (TIM1)
  HAL_TIM_Base_Start(&htim2);  // Start slave timer (TIM2) - synchronized to TIM1
}

int main(void)
{
  HAL_Init();
  MX_TIM1_Init();  // Initialize TIM1 (Master)
  MX_TIM2_Init();  // Initialize TIM2 (Slave)

  Start_Timers();  // Start both timers simultaneously

  while(1)
  {
    // Main loop
  }
}
