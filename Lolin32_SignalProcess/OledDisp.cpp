// OledDisp.cpp
#include "OledDisp.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int sdaPin = 19; // SDA pin
const int sclPin = 22; // SCL pin

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void oledInit() {
    Wire.begin(sdaPin, sclPin); // SDA, SCL

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
}

void displayText(const String& text1, const String& text2)
{
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(text1.c_str());

    display.setCursor(0, 30);
    display.println(text2.c_str());

    display.display();
}
