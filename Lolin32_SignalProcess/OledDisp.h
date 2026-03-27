// OledDisp.h
#ifndef OLED_DISP_H
#define OLED_DISP_H
#include <Arduino.h>

void oledInit();
void displayText(const String& text1, const String& text2);

#endif