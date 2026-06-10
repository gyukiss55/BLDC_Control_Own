// MainControl.cpp

#include <math.h>
#include "Clarke.h"
#include "Park.h"
#include "InvPark.h"
#include "SVPWM.h"
#include "OpenLoopRamp.h"

typedef enum
{
    STATE_ALIGN,
    STATE_OPEN_LOOP,
    STATE_RUN
} MotorState;

MotorState state = STATE_ALIGN;

float ia, ib;

float ialpha, ibeta;

float id, iq;

float vd, vq;

float valpha, vbeta;

float theta = 0;
float omega = 0;

float vbus = 24.0f;

float Id_ref = 0;
float Iq_ref = 1.0f; // torque

void Alignment(float dt)
{
    static float t = 0;
    t += dt;

    theta = 0;

    vd = 2.0f;   // DC magnetizing current
    vq = 0;

    InvPark();
    SVPWM(valpha, vbeta);

    if (t > 0.5f)
        state = STATE_OPEN_LOOP;
}

void PLL_Update(float dt)
{
    float s = sinf(theta);
    float c = cosf(theta);

    float eq = ibeta * c - ialpha * s;

    static float i = 0;
    i += eq * dt;

    float omega_pll = 50.0f * eq + i;

    theta += omega_pll * dt;

    if (theta > 6.2831853f)
        theta -= 6.2831853f;
}

void RunFOC(float dt)
{
    Clarke();
    Park();

    float errD = Id_ref - id;
    float errQ = Iq_ref - iq;

    vd = PI(errD);
    vq = PI(errQ);

    InvPark();
    SVPWM(valpha, vbeta);
  
    PLL_Update(dt);
}

void loopMain(float dt)
{
    switch (state)
    {
    case STATE_ALIGN:
        Alignment(dt);
        break;

    case STATE_OPEN_LOOP:
        OpenLoop(dt);
        break;

    case STATE_RUN:
        RunFOC(dt);
        break;
    }
}

void initPWM()
{
    gpio_set_function(10, GPIO_FUNC_PWM);
    gpio_set_function(11, GPIO_FUNC_PWM);
    gpio_set_function(12, GPIO_FUNC_PWM);

    pwm_set_wrap(0, 65535);
    pwm_set_enabled(0, true);
}
