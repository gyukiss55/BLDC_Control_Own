// Perplexity
// Black Pill STM32F411CE BLDC Control Project
// Select board: Generic F411CE in Arduino IDE with STM32 core

// Volatile global parameters
volatile int vol_m_control = 0;  // 0-Stop, 1-Async, 2-Listening, 3-Sync
volatile int vol_ti_ix = 0;      // Timer index
volatile uint32_t vol_ti_ts[32] = {0};  // Timer timestamps
volatile uint8_t vol_ti_BLDC[32] = {0}; // BLDC states (note: byte array)
volatile int vol_ei_ix = 0;      // External interrupt index
volatile uint32_t vol_ei_ts[32] = {0};  // EI timestamps micros
volatile int vol_ei_inp[32] = {0};     // EI inputs PA0,PA1,PA2 status

// BLDC pins: PB12,13,14,15,8,9 -> bits 12,13,14,15,8,9 in GPIOB->ODR
#define BLDC_MASK  ((1<<12)|(1<<13)|(1<<14)|(1<<15)|(1<<8)|(1<<9))

HardwareTimer *MyTim = NULL;

void TimerHandler(void) {
  uint32_t ts = micros();
  vol_ti_ts[vol_ti_ix] = ts;
  // Apply BLDC state - direct port access [web:21]
  GPIOB->ODR = (GPIOB->ODR & ~BLDC_MASK) | (vol_ti_BLDC[vol_ti_ix] & BLDC_MASK);
  vol_ti_ix = (vol_ti_ix + 1) % 32;
}

void ExtInterruptHandler() {
  uint32_t ts = micros();
  uint16_t inp = GPIOA->IDR & 0x07;  // PA0,PA1,PA2 bits 0,1,2
  vol_ei_ts[vol_ei_ix] = ts;
  vol_ei_inp[vol_ei_ix] = inp;
  vol_ei_ix = (vol_ei_ix + 1) % 32;
}

void setup() {
  // BLDC outputs PB12-PB15,PB8,PB9 [web:1]
  pinMode(PB12, OUTPUT);
  pinMode(PB13, OUTPUT);
  pinMode(PB14, OUTPUT);
  pinMode(PB15, OUTPUT);
  pinMode(PB8, OUTPUT);
  pinMode(PB9, OUTPUT);

  // External interrupts PA0,PA1,PA2 both directions (CHANGE) [web:20]
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA2, INPUT);
  attachInterrupt(PA0, ExtInterruptHandler, CHANGE);
  attachInterrupt(PA1, ExtInterruptHandler, CHANGE);
  attachInterrupt(PA2, ExtInterruptHandler, CHANGE);

  // Timer interrupt 10us period [web:16][web:13]
  // STM32F411 100MHz sysclk, timer x2 -> 200MHz, prescaler=1 (0), period=1999 (~10us)
  MyTim = new HardwareTimer(TIM2);
  MyTim->setOverflow(1999, TICK_FORMAT);  // 200MHz / 2000 = 100kHz = 10us
  MyTim->attachInterrupt(TimerHandler);
  MyTim->resume();

  Serial.begin(115200);
}

void loop() {
  // Example: set mode via serial or leave as is
  if (Serial.available()) {
    int cmd = Serial.parseInt();
    vol_m_control = cmd;
    Serial.print("Mode set to: ");
    Serial.println(vol_m_control);
  }

  // Mode-dependent logic can be added here
  // For now, arrays are filled by interrupts
  delay(100);
}
