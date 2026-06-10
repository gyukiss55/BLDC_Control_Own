
#pragma once

typedef struct
{
    float kp;
    float ki;

    float integral;
    float outMin;
    float outMax;
} PIController_t;

typedef struct
{
    float ia;
    float ib;

    float ialpha;
    float ibeta;

    float id;
    float iq;

    float vd;
    float vq;

    float valpha;
    float vbeta;

    float theta;

    float dutyA;
    float dutyB;
    float dutyC;
} FOC_t;

extern FOC_t foc;

void FOC_Init();
void FOC_Run(
    float ia,
    float ib,
    float thetaElectrical,
    float idRef,
    float iqRef,
    float vbus);
