// BLDCOledDisplay.h
#pragma once
#include <Adafruit_SSD1306.h>
#include "BLDCExternalInterrupt.h"

class BLDCOledDisplay {
public:
    BLDCOledDisplay();
    void begin();
    void update(float rpm, int dir);

private:
    Adafruit_SSD1306 display;
};
