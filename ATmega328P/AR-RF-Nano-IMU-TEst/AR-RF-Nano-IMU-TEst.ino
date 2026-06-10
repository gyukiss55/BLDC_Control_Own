
#include "WireScane.h"
#include "HMC_QMC5883LCompass.h"
#include "MPU6500_AcceGyro.h"
#include "BMP280_PressAlt.h"
#include "RF_Transmit.h"

void setup() {
	Serial.begin(115200);
    delay(2000);

	setupWire();
	for (int i = 0; i < 5; i++) {
		Serial.println("Starting I2C scan in...");
		loopWireScanner(1000);
	}
	stopWire();

	setupMPU6500();
	setupBMP280();
	setupQMC5883LCompass();

	setupRFTransmit();
}

void loop() {
	//loopQMC5883LCompassXYZ();
	//loopQMC5883LCompassBearing();
	//loopMPU6500();
	//loopBMP280(500);
	
	String msg = "T(ms):" + String(millis()) + "\n";
	String msgAll = msg;
	Serial.print(msg);

	dumpMPU6500(msg);
	msgAll += msg + "\n";
	Serial.println(msg);

	dumpBMP280(msg);
	msgAll += msg + "\n";
	Serial.println(msg);

	dumpQMC5883LCompass(msg);
	msg += "\n----\n";
	msgAll += msg;
	Serial.print(msg);

	Serial.println("Transmitting data:" + String(msgAll.length()));
	startRFTransmit(msgAll);

	delay(100);
}
