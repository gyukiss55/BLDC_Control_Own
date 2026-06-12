//PWMControl.cpp
#include <Arduino.h>
#include <list>
#include "PWMControl.h"

uint32_t pwmValue[4] = {1000, 1000, 1000, 1000};
char* pattern[] = { "1/", "2/", "3/", "4/" };

void setupPWM() {
	analogWriteFrequency(10);      // 10 Hz = 100 ms period

	analogWrite(PA0, pwmValue[0]);
	analogWrite(PA1, pwmValue[1]);
	analogWrite(PA2, pwmValue[2]);
	analogWrite(PA3, pwmValue[3]);
}

void loopPWM() {
	if (Serial.available() > 0) {
		std::list<int> indeces;
		String input = Serial.readStringUntil('\n');
		for (int i = 0; i < 4; i++) {
			if (input.startsWith(pattern[i])) {
				input = input.substring(strlen(pattern[i])); // Remove the pattern prefix

				Serial.print("Found pattern: ");
				Serial.println(input);

				int value = input.toInt();
				if (value >= 0 && value <= 10000) {
					pwmValue[i] = value + 1000; // Update the PWM value for the corresponding pin
					indeces.push_back(i);

					Serial.print("PWM");
					Serial.print(i+1);
					Serial.print("=");
					Serial.println(pwmValue[i]);

				}
				int index = input.indexOf(pattern[i+1]);
				if (index != -1) {
					input = input.substring(index);
					Serial.print("PWM next");
					Serial.println(input);
				}
			}
		}
		for (int index : indeces) {
			Serial.print("Updated PWM");
			Serial.print(index+1);
			Serial.print("=");
			Serial.println(pwmValue[index]);
			switch (index) {
			case 0:
				analogWrite(PA0, pwmValue[0]);
				break;
			case 1:
				analogWrite(PA1, pwmValue[1]);
				break;
			case 2:
				analogWrite(PA2, pwmValue[2]);
				break;
			case 3:
				analogWrite(PA3, pwmValue[3]);
				break;
			}
		}
	}
	// Update the PWM outputs with the new values
}