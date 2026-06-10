

void FOC_Control()
{
    FOC_Run(
        ia,
        ib,
        electricalAngle,
        0.0f,      // Id_ref
        torqueCmd, // Iq_ref
        24.0f);    // DC bus

    uint16_t wrap = pwm_get_wrap(slice);

    pwm_set_chan_level(
        sliceA,
        PWM_CHAN_A,
        foc.dutyA * wrap);

    pwm_set_chan_level(
        sliceB,
        PWM_CHAN_A,
        foc.dutyB * wrap);

    pwm_set_chan_level(
        sliceC,
        PWM_CHAN_A,
        foc.dutyC * wrap);
}
