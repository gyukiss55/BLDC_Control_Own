#include "FOC.h"

#include <math.h>

#define INV_SQRT3 0.57735026919f
#define SQRT3     1.73205080757f

FOC_t foc;

static PIController_t piD;
static PIController_t piQ;

void FOC_Init()
{
    piD.kp = 0.5f;
    piD.ki = 100.0f;

    piD.outMin = -12.0f;
    piD.outMax = 12.0f;

    piQ.kp = 0.5f;
    piQ.ki = 100.0f;

    piQ.outMin = -12.0f;
    piQ.outMax = 12.0f;
}

void FOC_Run(
    float ia,
    float ib,
    float theta,
    float idRef,
    float iqRef,
    float vbus)
{
    const float dt = 0.00005f;

    foc.ia = ia;
    foc.ib = ib;

    foc.theta = theta;

    Clarke(
        ia,
        ib,
        &foc.ialpha,
        &foc.ibeta);

    Park(
        foc.ialpha,
        foc.ibeta,
        theta,
        &foc.id,
        &foc.iq);

    float errD =
        idRef - foc.id;

    float errQ =
        iqRef - foc.iq;

    foc.vd =
        PI_Run(
            &piD,
            errD,
            dt);

    foc.vq =
        PI_Run(
            &piQ,
            errQ,
            dt);

    InvPark(
        foc.vd,
        foc.vq,
        theta,
        &foc.valpha,
        &foc.vbeta);

    SVPWM(
        foc.valpha,
        foc.vbeta,
        vbus,
        &foc.dutyA,
        &foc.dutyB,
        &foc.dutyC);
}

