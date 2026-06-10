// FOC_Sensorless.cpp
/*
Known: rotor angle θe
Unknown: Vα, Vβ + Iα, Iβ

Ia, Ib
Clarke
Iα, Iβ
Observer (Back-EMF)
eα, eβ
atan / Park error
PLL
θe
Park / Inverse Park
SVPWM

L-R modell:
eα=Vα−Riα−L*diα/dt
eb=Vb−Rib−L*dib/dt

*/

static float R = 0.2f;
static float L = 0.0003f;

static float iAlphaPrev = 0;
static float iBetaPrev = 0;

void EstimateBackEMF(
    float Valpha, float Vbeta,
    float Ialpha, float Ibeta,
    float dt,
    float* ealpha,
    float* ebeta)
{
    float diAlpha = (Ialpha - iAlphaPrev) / dt;
    float diBeta = (Ibeta - iBetaPrev) / dt;

    *ealpha = Valpha - R * Ialpha - L * diAlpha;
    *ebeta = Vbeta - R * Ibeta - L * diBeta;

    iAlphaPrev = Ialpha;
    iBetaPrev = Ibeta;
}

typedef struct
{
    float kp;
    float ki;
    float integrator;
} PLL_t;

PLL_t pll;

float PLL_Run(float eq, float dt)
{
    pll.integrator += pll.ki * eq * dt;

    float omega =
        pll.kp * eq +
        pll.integrator;

    return omega; // electrical speed
}

float theta_e = 0;

void UpdateAngle(float omega, float dt)
{
    theta_e += omega * dt;

    if (theta_e > 6.2831853f)
        theta_e -= 6.2831853f;

    if (theta_e < 0)
        theta_e += 6.2831853f;
}

void SensorlessFOC(float Ia, float Ib,
    float Valpha, float Vbeta,
    float dt)
{
    // 1. Clarke
    float Ialpha = Ia;
    float Ibeta = -(2 * Ib + Ia) * 0.577350269f;

    // 2. Back-EMF
    float ealpha, ebeta;

    EstimateBackEMF(
        Valpha, Vbeta,
        Ialpha, Ibeta,
        dt,
        &ealpha,
        &ebeta);

    // 3. PLL error (q-axis EMF)
    float eq =
        ebeta * cosf(theta_e) -
        ealpha * sinf(theta_e);

    // 4. PLL speed
    float omega = PLL_Run(eq, dt);

    // 5. Angle update
    UpdateAngle(omega, dt);

    // 6. Park transform
    float s = sinf(theta_e);
    float c = cosf(theta_e);

    float Id = Ialpha * c + Ibeta * s;
    float Iq = -Ialpha * s + Ibeta * c;

    // 7. PI control
    float Vd = PI_d(Id_ref - Id);
    float Vq = PI_q(Iq_ref - Iq);

    // 8. Inverse Park
    Valpha = Vd * c - Vq * s;
    Vbeta = Vd * s + Vq * c;

    // 9. SVPWM
    SVPWM(Valpha, Vbeta);
}

