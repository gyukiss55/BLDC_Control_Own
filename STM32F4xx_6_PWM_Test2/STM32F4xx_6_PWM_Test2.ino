HardwareTimer *Timer3 = new HardwareTimer(TIM3); // For PA6, PA7
HardwareTimer *Timer4 = new HardwareTimer(TIM4); // For PB7, PB8, PB9
HardwareTimer *Timer5 = new HardwareTimer(TIM5); // For PA0

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("PWM A6, A7, B7, B8, B9, A0 (50, 25, 60, 40, 75, 30)");

  LED_Init();
  // --- Setup PWM at 100 kHz ---
  
//  Timer3->setPWM(1, PA6, 100000, 50);  // 100kHz, 50% duty
//  Timer3->setPWM(2, PA7, 100000, 25);  // 100kHz, 25% duty

  Timer4->setPWM(2, PB7, 100000, 60);  // 100kHz, 60% duty
  Timer4->setPWM(3, PB8, 100000, 40);  // 100kHz, 40% duty
  Timer4->setPWM(4, PB9, 100000, 75);  // 100kHz, 75% duty

//  Timer5->setPWM(1, PA0, 100000, 30);  // 100kHz, 30% duty
  
}

void loop() {
  // Nothing needed in loop unless dynamic updates required
  static int duty = 0;
  static uint32_t tsLast = 0;
  Timer4->setCaptureCompare(2, duty, PERCENT_COMPARE_FORMAT); // PB7 = TIM4_CH2
  duty = (duty + 1) % 100;
  delay(100);

  uint32_t tsCurrent = millis ();
  if (tsCurrent - tsLast >= 1000) {
    tsLast = tsLast + 1000;
    Serial.print(tsCurrent);
    Serial.print(" duty:");
    Serial.print(duty);
    Serial.println(" ");
  }

  LED_Toggle ();
}

void LED_Init()
{
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);

}

void LED_Toggle()
{
  static uint32_t tsLastLED = 0;
  static bool status = false;
  uint32_t tsCurrent = millis();
  if (status && (tsCurrent - tsLastLED) > 200){
    digitalWrite(PC13, HIGH);
    status = !status;
    tsLastLED = tsCurrent;

  } else if (!status && (tsCurrent - tsLastLED) > 300){
    digitalWrite(PC13, LOW);
    status = !status;
    tsLastLED = tsCurrent;
  }
 

}