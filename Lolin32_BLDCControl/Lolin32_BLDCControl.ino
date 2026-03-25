#include <Arduino.h>

// ---------------- PIN DEFINITIONS ----------------
#define LED_BUILTIN 22

#define PWM_PIN 12

#define AH_PIN 14
#define AL_PIN 25
#define BH_PIN 32
#define BL_PIN 33
#define CH_PIN 26
#define CL_PIN 27

#define COMP1_PIN 13
#define COMP2_PIN 15
#define COMP3_PIN 2

// ---------------- GLOBALS ----------------
volatile uint32_t pwmDuty = 0;
volatile uint32_t bldcPeriod = 50; // ms

volatile uint32_t newPwmDuty = 0;
volatile uint32_t newBldcPeriod = 50;
volatile bool updatePending = false;

const int driveCycle = 6 * 30;
const int emptyCycle = 6 * 10;
volatile int driveCycleCounter = 0;

// External interrupt logging
volatile uint32_t tsExtInt[32];
volatile byte stateExtInt[32];
volatile int extIntIndex = 0;
volatile uint32_t extIntCounter = 0;

// BLDC state
volatile uint8_t commState = 0;

// Timer
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// PWM config

const int pwmFreq = 1000;
const int pwmResolution = 10; // 1024 steps

// ---------------- BLDC COMMUTATION ----------------
void IRAM_ATTR setCommutation(uint8_t state)
{
    // Turn everything OFF first
    digitalWrite(AH_PIN, LOW);
    digitalWrite(AL_PIN, LOW);
    digitalWrite(BH_PIN, LOW);
    digitalWrite(BL_PIN, LOW);
    digitalWrite(CH_PIN, LOW);
    digitalWrite(CL_PIN, LOW);

    switch (state)
    {
    case 0: digitalWrite(AH_PIN, HIGH); digitalWrite(BL_PIN, HIGH); break;
    case 1: digitalWrite(AH_PIN, HIGH); digitalWrite(CL_PIN, HIGH); break;
    case 2: digitalWrite(BH_PIN, HIGH); digitalWrite(CL_PIN, HIGH); break;
    case 3: digitalWrite(BH_PIN, HIGH); digitalWrite(AL_PIN, HIGH); break;
    case 4: digitalWrite(CH_PIN, HIGH); digitalWrite(AL_PIN, HIGH); break;
    case 5: digitalWrite(CH_PIN, HIGH); digitalWrite(BL_PIN, HIGH); break;
    }
}

// ---------------- TIMER ISR ----------------
void IRAM_ATTR onTimer()
{
    portENTER_CRITICAL_ISR(&timerMux);

    commState = (commState + 1) % 6;
    setCommutation(commState);

    // Apply deferred updates
    if (updatePending) {
        driveCycleCounter = 0; // reset drive cycle counter on parameter change
        pwmDuty = newPwmDuty;
        bldcPeriod = newBldcPeriod;
        ledcWrite(PWM_PIN, pwmDuty);

        // Update timer period
        uint64_t alarm = (uint64_t)bldcPeriod * 1000 / 6; // us per comm step
        timerAlarm(timer, alarm, true, 0);

        updatePending = false;
    }
    if (driveCycleCounter == driveCycle) 
        ledcWrite(PWM_PIN, 0);
    else    
        if (driveCycleCounter >= driveCycle + emptyCycle) {
            driveCycleCounter = 0;
            ledcWrite(PWM_PIN, pwmDuty);
        }
    driveCycleCounter++;

    portEXIT_CRITICAL_ISR(&timerMux);
}

// ---------------- EXTERNAL INTERRUPT ----------------
void IRAM_ATTR extInterruptHandler()
{
    extIntCounter++;

    tsExtInt[extIntIndex] = micros();

    byte state = 0;
    if (digitalRead(COMP1_PIN)) state |= 1;
    if (digitalRead(COMP2_PIN)) state |= 2;
    if (digitalRead(COMP3_PIN)) state |= 4;

    stateExtInt[extIntIndex] = state;

    extIntIndex = (extIntIndex + 1) % 32;
}

// ---------------- SERIAL COMMAND ----------------
void handleSerial()
{
    static String input = "";

    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\n')
        {
            if (input.startsWith("p"))
            {
                newBldcPeriod = input.substring(1).toInt();
                updatePending = true;
            }
            else if (input.startsWith("d"))
            {
                newPwmDuty = constrain(input.substring(1).toInt(), 0, 1023);
                updatePending = true;
            }
            else if (input.startsWith("-p")) {
                newBldcPeriod -= 5;
                updatePending = true;
            }
            else if (input.startsWith("+p")) {
                newBldcPeriod += 5;
                updatePending = true;
            }
            else if (input.startsWith("-d")) {
                newPwmDuty -= 5;
                updatePending = true;
            }
            else if (input.startsWith("+d")) {
                newPwmDuty += 5;
                updatePending = true;
            }
            input = "";
        }
        else
        {
            input += c;
        }
    }
}

// ---------------- SETUP ----------------
void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(AH_PIN, OUTPUT);
    pinMode(AL_PIN, OUTPUT);
    pinMode(BH_PIN, OUTPUT);
    pinMode(BL_PIN, OUTPUT);
    pinMode(CH_PIN, OUTPUT);
    pinMode(CL_PIN, OUTPUT);

    pinMode(COMP1_PIN, INPUT);
    pinMode(COMP2_PIN, INPUT);
    pinMode(COMP3_PIN, INPUT);

    // PWM setup
    pinMode(PWM_PIN, OUTPUT);
    ledcAttach(PWM_PIN, pwmFreq, pwmResolution);
    ledcWrite(PWM_PIN, pwmDuty);

    // External interrupts
    attachInterrupt(COMP1_PIN, extInterruptHandler, CHANGE);
    attachInterrupt(COMP2_PIN, extInterruptHandler, CHANGE);
    attachInterrupt(COMP3_PIN, extInterruptHandler, CHANGE);

    // Timer setup
    timer = timerBegin(1000000); // 1 MHz timer
    timerAttachInterrupt(timer, &onTimer);

    uint64_t alarm = (uint64_t)bldcPeriod * 1000 / 6;
    timerAlarm(timer, alarm, true, 0);
}

// ---------------- LOOP ----------------
void loop()
{
    static uint32_t lastPrint = 0;
    static bool led_builtin_off = false;

    handleSerial();

    if (millis() - lastPrint >= 1000)
    {
        digitalWrite(LED_BUILTIN, LOW);
        led_builtin_off = true;
        lastPrint = millis();

        Serial.print("ms: ");
        Serial.print(millis());
        Serial.print(" duty: ");
        Serial.print(pwmDuty);
        Serial.print(" period: ");
        Serial.print(bldcPeriod);
        Serial.print(" extIntCnt: ");
        Serial.println(extIntCounter);
        //digitalWrite(LED_BUILTIN, HIGH);
    }
    if (led_builtin_off && millis() - lastPrint >= 100)
    {
        led_builtin_off = false;
        digitalWrite(LED_BUILTIN, HIGH);
    }
}
