// PicoPWMControl_old

#ifdef _PICOPWMCONTROL_OLD_


#include <Arduino.h>

const int pwmPin = 15;
const int period_us = 20000; // 20 ms (50 Hz)

String inputString = "";
bool inputComplete = false;

void setup_old() {
    Serial.begin(115200);

    pinMode(pwmPin, OUTPUT);

    analogWriteFreq(50);        // 50 Hz
    analogWriteRange(65535);    // 16-bit resolution

    Serial.println("Enter pulse width in ms (e.g. 1.0 - 2.0):");
}

void loop_old() {
    if (inputComplete) {
        float pulse_ms = inputString.toFloat();
        int pulse_us = pulse_ms * 1000;

        // Clamp to safe ESC range
        if (pulse_us < 1000) pulse_us = 1000;
        if (pulse_us > 2000) pulse_us = 2000;

        // Convert to duty cycle
        float duty = (float)pulse_us / period_us;
        uint16_t pwmValue = duty * 65535;

        analogWrite(pwmPin, pwmValue);

        Serial.print("Set pulse: ");
        Serial.print(pulse_ms);
        Serial.print(" ms (");
        Serial.print(pulse_us);
        Serial.println(" us)");

        inputString = "";
        inputComplete = false;
    }
}

// Serial event handler
void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();

        if (inChar == '\n') {
            inputComplete = true;
        }
        else {
            inputString += inChar;
        }
    }
}

#endif // _PICOPWMCONTROL_OLD_
