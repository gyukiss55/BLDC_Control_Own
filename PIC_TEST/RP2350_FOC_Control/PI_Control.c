static float PI_Run(
    PIController_t* pi,
    float error,
    float dt)
{
    pi->integral += error * pi->ki * dt;

    if (pi->integral > pi->outMax)
        pi->integral = pi->outMax;

    if (pi->integral < pi->outMin)
        pi->integral = pi->outMin;

    float out =
        pi->kp * error +
        pi->integral;

    if (out > pi->outMax)
        out = pi->outMax;

    if (out < pi->outMin)
        out = pi->outMin;

    return out;
}
