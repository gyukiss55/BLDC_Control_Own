
volatile uint8_t sector;
volatile uint32_t sectorTime;
volatile uint32_t prevSectorTime;
volatile uint32_t sectorPeriod;

uint8_t ReadSector()
{
    uint8_t x = digitalRead(19);
    uint8_t y = digitalRead(20);
    uint8_t z = digitalRead(21);

    uint8_t state =
        (x << 2) |
        (y << 1) |
        z;

    switch (state)
    {
    case 0b100: return 0;
    case 0b110: return 1;
    case 0b010: return 2;
    case 0b011: return 3;
    case 0b001: return 4;
    case 0b101: return 5;
    }

    return sector;
}

void ObserverUpdate()
{
    uint8_t newSector =
        ReadSector();

    if (newSector != sector)
    {
        prevSectorTime =
            sectorTime;

        sectorTime =
            micros();

        sectorPeriod =
            sectorTime -
            prevSectorTime;

        sector =
            newSector;
    }
}

float GetElectricalAngle()
{
    uint32_t dt =
        micros() - sectorTime;

    float inside =
        60.0f *
        ((float)dt /
            (float)sectorPeriod);

    if (inside > 60.0f)
        inside = 60.0f;

    float angle =
        sector * 60.0f +
        inside;

    return angle *
        0.01745329252f;
}

void RotorAngle_Update()
{
    // Your rotor angle update logic here
}