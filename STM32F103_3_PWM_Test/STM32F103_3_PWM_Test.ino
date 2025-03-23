TIM_TypeDef *Instance = TIM4;
HardwareTimer *MyTim = new HardwareTimer(Instance);

void setup() {
  MyTim->setPWM(2, PB7, 20000, 50); // Channel 2, 20 kHz, 50% duty
  MyTim->setPWM(3, PB8, 20000, 20); // Channel 2, 20 kHz, 50% duty
  MyTim->setPWM(4, PB9, 20000, 70); // Channel 2, 20 kHz, 50% duty
}

void loop ()
{
  static uint32_t duty = 0;
  static uint32_t lastTsDuty = 0;
  uint32_t currentTs = millis ();
  if (currentTs - lastTsDuty > 100) {
    lastTsDuty = currentTs;
    duty++;
    if (duty >= 100)
      duty = 0;
    MyTim->setCaptureCompare(2, duty);

  }
}