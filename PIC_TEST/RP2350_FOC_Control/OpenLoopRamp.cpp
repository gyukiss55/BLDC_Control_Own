// OpenLoopRamp.cpp
//         pll.integrator;

float omega = 2.0f * 3.14159f * 2.0f; // 2 Hz indulás
float omegaRamp = 50.0f;              // rad/s^2
float theta = 0;

void OpenLoopRamp(float dt)
{
    // 1. sebesség növelés
    omega += omegaRamp * dt;

    // 2. szög integrálás
    theta += omega * dt;

    if (theta > 6.2831853f)
        theta -= 6.2831853f;

    // 3. referencia áramok
    float Id = Id_ref;   // fluxus
    float Iq = Iq_ref;   // nyomaték

    // 4. Park inverse (szimulált rotor pozíció)
    float s = sinf(theta);
    float c = cosf(theta);

    float Valpha =
        Id * c - Iq * s;

    float Vbeta =
        Id * s + Iq * c;

    // 5. PWM
    SVPWM(Valpha, Vbeta);
}
 