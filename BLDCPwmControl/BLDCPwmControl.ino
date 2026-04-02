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
    delay(2000);
    Serial.println("Setup serial done");
    delay(1000);
    pwm.begin(13);          // ESC signal pin
    Serial.println("Setup pwm done");
    //sensor.begin(4);        // Hall sensor pin
    //oled.begin();
    Serial.println("Setup OLED done");
    //net.begin();
    Serial.println("Setup NET done");
    Serial.println("BLDC PWM setup done!");
}

void loop() {
    //net.handleClient();

    //float rpm = sensor.getRPM();
    //int dir = sensor.getDirection();

    //oled.update(pwm.period(), pwm.duty());

    delay(200);
}
