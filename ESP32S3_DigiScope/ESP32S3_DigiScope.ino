#include "ESP32C3DigiInput.h"
#include "ESP32C3DigiOutput.h"
#include "ESP32S3RGB.h"


void setup() {
	Serial.begin(115200);
	delay(1000); // Wait for serial to initialize
	Serial.println("ESP32C3 Digital Scope Example");

	setupESP32S3RGB();
	setupESP32C3DigiInput();
	setupESP32C3DigiOutput();

}

void loop() {
  // put your main code here, to run repeatedly:
	loopDigitalOutput(1000); // Change output state every 200ms
	loopDigitalInput(200);
	//BlinkLed();
}


