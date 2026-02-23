#include "ESP32C3DigiInput.h"
#include "ESP32C3DigiOutput.h"
#include "ESP32S3RGB.h"


void setup() {
	Serial.begin(115200);
	delay(1000); // Wait for serial to initialize
	Serial.println("ESP32C3 Digital Scope Example V0.82");
	setupESP32S3RGB();
	unitTestRGB();
	setRGB(255, 0, 0); // Set initial color to red
	delay(1000);
		
	setupESP32C3DigiInput();
	setRGB(0, 0, 255); // Set initial color to blue
	delay(1000);

	setupESP32C3DigiOutput();
	setRGB(0, 255, 0); // Set initial color to green
	delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
	loopDigitalOutput(1000); // Change output state every 200ms
	loopDigitalInput(50);
	//BlinkLed();
}


