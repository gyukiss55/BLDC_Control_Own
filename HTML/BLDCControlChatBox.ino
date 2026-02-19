// ChatBox recept
// Include necessary libraries for STM32
#include <STM32FreeRTOS.h> // For FreeRTOS functionality
#include <Arduino.h>

// Define BLDC (0-5) output pins
#define BLDC0_PIN PB12
#define BLDC1_PIN PB13
#define BLDC2_PIN PB14
#define BLDC3_PIN PB15
#define BLDC4_PIN PB8
#define BLDC5_PIN PB9

// Define external interrupt input pins
#define EI0_PIN PA0
#define EI1_PIN PA1
#define EI2_PIN PA2

// Global variables
volatile int vol_m_control = 0; // Motor control state
volatile int vol_ti_ix = 0; // Timer index
volatile uint32_t vol_ti_ts[32] = {0}; // Timer timestamps
volatile byte vol_ti_BLDC = 0; // BLDC state
volatile int vol_ei_ix = 0; // External interrupt index
volatile uint32_t vol_ei_ts[32] = {0}; // External interrupt timestamps
volatile int vol_ei_inp[32] = {0}; // External interrupt input states

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize BLDC output pins
  pinMode(BLDC0_PIN, OUTPUT);
  pinMode(BLDC1_PIN, OUTPUT);
  pinMode(BLDC2_PIN, OUTPUT);
  pinMode(BLDC3_PIN, OUTPUT);
  pinMode(BLDC4_PIN, OUTPUT);
  pinMode(BLDC5_PIN, OUTPUT);

  // Initialize external interrupt pins
  pinMode(EI0_PIN, INPUT_PULLUP);
  pinMode(EI1_PIN, INPUT_PULLUP);
  pinMode(EI2_PIN, INPUT_PULLUP);

  // Attach external interrupts
  attachInterrupt(digitalPinToInterrupt(EI0_PIN), handleExternalInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EI1_PIN), handleExternalInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(EI2_PIN), handleExternalInterrupt, CHANGE);

  // Start timer interrupt
  Timer1.initialize(10); // Set timer period to 10 microseconds
  Timer1.attachInterrupt(handleTimerInterrupt); // Attach the interrupt handler
}

void loop() {
  // Main loop - Implement your control logic here
}

// Timer interrupt handler
void handleTimerInterrupt() {
  // Update the timer index and state
  vol_ti_ix = (vol_ti_ix + 1) % 32; // Increment and wrap index
  vol_ti_ts[vol_ti_ix] = micros(); // Store the current time in microseconds

  // Add your BLDC control logic here, e.g., update vol_ti_BLDC state
}

// External interrupt handler
void handleExternalInterrupt() {
  // Read the states of the external interrupt pins
  vol_ei_inp[vol_ei_ix] = (digitalRead(EI0_PIN) << 0) | (digitalRead(EI1_PIN) << 1) | (digitalRead(EI2_PIN) << 2);
  vol_ei_ts[vol_ei_ix] = micros(); // Store timestamp for the change
  vol_ei_ix = (vol_ei_ix + 1) % 32; // Increment and wrap index
 
  // Add your handling logic here, e.g., update vol_m_control based on input states
}
