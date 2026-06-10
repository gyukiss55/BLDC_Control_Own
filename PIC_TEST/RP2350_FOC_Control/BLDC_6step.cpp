/* BLDC 6-step Control

Fázis	Állapot
A		HIGH / PWM
B		LOW
C		FLOAT

Sector	High	Low	Float
0	A	B	C
1	A	C	B
2	B	C	A
3	B	A	C
4	C	A	B
5	C	B	A


PWM1 = A (GP10)
PWM2 = B (GP11)
PWM3 = C (GP12)

*/

volatile uint32_t lastEdge = 0;
volatile uint32_t period = 0;

void EdgeISR()
{
    uint32_t now = micros();

    period = now - lastEdge;

    lastEdge = now;
}

float GetRPM()
{
    if (period == 0) return 0;

    float freq = 1e6f / period;

    return (freq / 6.0f) * 60.0f;
}

void SetPhasePWM(uint8_t high, uint8_t low, uint8_t floating, float duty)
{
    // floating = OFF

    analogWrite(floating, 0);

    analogWrite(low, 0);

    analogWrite(high, duty);
}

void BLDC_6Step(uint8_t sector, float duty)
{
    switch (sector)
    {
    case 0:
        SetPhasePWM(10, 11, 12, duty); // A+ B- C float
        break;

    case 1:
        SetPhasePWM(10, 12, 11, duty); // A+ C- B float
        break;

    case 2:
        SetPhasePWM(11, 12, 10, duty); // B+ C- A float
        break;

    case 3:
        SetPhasePWM(11, 10, 12, duty); // B+ A- C float
        break;

    case 4:
        SetPhasePWM(12, 10, 11, duty); // C+ A- B float
        break;

    case 5:
        SetPhasePWM(12, 11, 10, duty); // C+ B- A float
        break;
    }
}

float speedPI(float ref, float rpm)
{
    static float i = 0;

    float err = ref - rpm;

    i += err * 0.01f;

    float out =
        0.1f * err +
        0.05f * i;

    if (out > 0.95f) out = 0.95f;
    if (out < 0.05f) out = 0.05f;

    return out;
}

void loopBLDC_6_Step()
{
    uint8_t sector = GetSector();

    float rpm = GetRPM();

    float duty = speedPI(targetRPM, rpm);

    BLDC_6Step(sector, duty);
}

