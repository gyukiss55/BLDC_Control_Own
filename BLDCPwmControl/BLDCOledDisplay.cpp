// BLDCOledDisplay.cpp
#include "BLDCOledDisplay.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

BLDCOledDisplay::BLDCOledDisplay()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
}

void BLDCOledDisplay::begin() {
    Wire.begin(19, 22);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
}

void BLDCOledDisplay::update(float rpm, int dir) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("RPM:");
    display.println(rpm);

    display.setTextSize(1);
    display.print("DIR: ");
    display.println(dir > 0 ? "CW" : "CCW");

    display.display();
}
