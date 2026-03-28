// PwmSignal.cpp

#include "PwmSignal.h"
#include <Arduino.h>


#define PIN_PWM1 13
#define PIN_PWM2 15


//#define PWM_FREQ 80000
#define PWM_FREQ 50000
#define PWM_RES 10

const int MaxValuePWM = (1 << PWM_RES) - 1;
int periodSign1 = 1181;
int periodSign2 = 1321;

int sinTable[90];

static int fastSin(int deg) {
    deg %= 360;
    if (deg < 0) deg += 360;

    if (deg < 90) return sinTable[deg];
    if (deg < 180) return sinTable[180 - deg];
    if (deg < 270) return -sinTable[deg - 180];
    return -sinTable[360 - deg];
}

void pwmInit() {
    // init sine table
    for (int i = 0; i < 90; i++) {
        sinTable[i] = (int)(1000.0 * sin(i * PI / 180.0));
    }

    ledcAttach(PIN_PWM1, PWM_FREQ, PWM_RES);
    ledcAttach(PIN_PWM2, PWM_FREQ, PWM_RES);

    ledcWrite(PIN_PWM1, 0);
    ledcWrite(PIN_PWM2, 0);

}

void pwmUpdate() {
    uint32_t t = micros();

    // T1 = 1 ms
    float phase1 = (t % periodSign1) * 360.0 / 1000.0;

    // T2 = 8/7 ms ≈ 1143 us
    float phase2 = (t % periodSign2) * 360.0 / 1143.0;

    int s1 = fastSin((int)phase1);
    int s2 = fastSin((int)phase2);

    int pwm1 = (s1 + 1000) / 2;
    int pwm2 = (s2 + 1000) / 2;

    pwm1 = map(pwm1, 0, 1000, 0, MaxValuePWM);
    pwm2 = map(pwm2, 0, 1000, 0, MaxValuePWM);

    ledcWrite(PIN_PWM1, pwm1);
    ledcWrite(PIN_PWM2, pwm2);
}
