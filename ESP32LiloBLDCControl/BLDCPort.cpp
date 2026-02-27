#include "BLDCPort.h"

#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/soc.h"

// ================= GPIO DEFINITIONS =================

#define AH 12
#define AL 14
#define BH 27
#define BL 26
#define CH 25
#define CL 33

#define PWM_PIN 22

// ================= PWM CONFIG =================

#define PWM_CHANNEL 32
#define PWM_TIMER_BITS 10      // 10-bit resolution (1024 steps)
#define PWM_FREQ 50000        // 50 kHz (20 µs period)

#define PWM_LOW_TIMER_BITS 8      // 8-bit resolution (256 steps)
#define PWM_LOW_FREQ 200000        // 200 kHz (5 µs period)

// ================= TIMER =================

hw_timer_t* bldcTimer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile uint8_t phase = 0;
volatile uint32_t phasePeriod = 1000000;  // default 10000000us

int portPins[] = {AH,AL,BH,BL,CH,CL};

// ================= PHASE CONTROL =================

void IRAM_ATTR setPhase(uint8_t p)
{
    // Clear all
    /*
    GPIO.out_w1tc = ((1UL << AH) |
        (1UL << AL) |
        (1UL << BH) |
        (1UL << BL) |
        (1UL << CH) |
        (1UL << CL));
    */
	digitalWrite(AH, LOW);
	digitalWrite(AL, LOW);
	digitalWrite(BH, LOW);
	digitalWrite(BL, LOW);
	digitalWrite(CH, LOW);
	digitalWrite(CL, LOW);

	switch (p)
	{
	case 0:
		digitalWrite(AH, HIGH);
		digitalWrite(BL, HIGH);
		break; // AH-BL
	case 1:
		digitalWrite(AH, HIGH);
		digitalWrite(CL, HIGH);
		break; // AH-CL
	case 2:
		digitalWrite(BH, HIGH);
		digitalWrite(CL, HIGH);
		break; // BH-CL
	case 3:
		digitalWrite(BH, HIGH);
		digitalWrite(AL, HIGH);
		break; // BH-AL
	case 4:
		digitalWrite(CH, HIGH);
		digitalWrite(AL, HIGH);
		break; // CH-AL
	case 5:
		digitalWrite(CH, HIGH);
		digitalWrite(BL, HIGH);
		break; // CH-BL
	}
}

// ================= TIMER ISR =================

void IRAM_ATTR onBLDCTimer()
{
	portENTER_CRITICAL_ISR(&timerMux);

	phase++;
	if (phase >= 6) phase = 0;

	setPhase(phase);

	portEXIT_CRITICAL_ISR(&timerMux);
}

// ================= PUBLIC FUNCTIONS =================

void setupBLDCPort()
{
    // Set phase pins as output
    pinMode(AH, OUTPUT);
    pinMode(AL, OUTPUT);
    pinMode(BH, OUTPUT);
    pinMode(BL, OUTPUT);
    pinMode(CH, OUTPUT);
    pinMode(CL, OUTPUT);

    digitalWrite(AH, LOW);
    digitalWrite(AL, LOW);
    digitalWrite(BH, LOW);
    digitalWrite(BL, LOW);
    digitalWrite(CH, LOW);
    digitalWrite(CL, LOW);

    // ===== PWM Setup =====
    ledcAttach(PWM_CHANNEL, PWM_FREQ, PWM_TIMER_BITS);
  
    ledcWrite(PWM_CHANNEL, 1);  // 0 duty

    // Set timer frequency to 1Mhz
    bldcTimer = timerBegin(1000000);
    timerAttachInterrupt(bldcTimer, &onBLDCTimer);
    timerAlarm(bldcTimer, 100000, true, 0);

}

// Set phase period (µs)
int setBLDCPeriod(int usec)
{
    if (usec <= 0) return -1;

    portENTER_CRITICAL(&timerMux);
    phasePeriod = usec;
    timerAlarm(bldcTimer, phasePeriod, true, 0);
    portEXIT_CRITICAL(&timerMux);

    return 0;
}

// Set PWM duty (0–1023)
int setBLDCPWM(int duty)
{
    if (duty < 0) duty = 0;
    if (duty > 1023) duty = 1023;

    ledcWrite(PWM_CHANNEL, duty);

    return 0;
}

void loopBLDCPort()
{
    static uint32_t tsLast = 0;
    uint32_t tsNow = millis();
    if (tsNow - tsLast >= 100) {
        tsLast +=1000;
        String str = String (tsNow) + "- ";
        str = String(phase) + ",";
        for(int i = 0; i < 6; i++) {
            str+= String (digitalRead(portPins[i]));
            if (i < 5)
                str+= ",";
        }
        Serial.println(str);
    }
}