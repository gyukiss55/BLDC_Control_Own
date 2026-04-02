// BLDCPwmControl.ino - A simple BLDC motor controller using PWM signals.
#include "BLDCPWMControl.h"
#include "BLDCPWMNet.h"
#include "BLDCExternalInterrupt.h"
#include "BLDCOledDisplay.h"

BLDCPWMControl pwm;
BLDCPWMNet net(&pwm);
BLDCExternalInterrupt sensor;
BLDCOledDisplay oled;

void setup() {
    Serial.begin(115200);

    pwm.begin(18);          // ESC signal pin
    sensor.begin(4);        // Hall sensor pin
    oled.begin();

    net.begin();
}

void loop() {
    net.handleClient();

    float rpm = sensor.getRPM();
    int dir = sensor.getDirection();

    oled.update(rpm, dir);

    delay(200);
}
