
#include <Arduino.h>
#include <list>
#include "LedBlink.h"
#include "WireScan.h"
#include "HMC_QMC5883LCompass.h"
#include "MPU6500_AcceGyro.h"
#include "BMP280_PressAlt.h"
#include "TimerTrigger.h"
#include "PWMControl.h"

TimerTrigger imuTimer;

void setup() {
	Serial.begin(115200);
	setupPWM();
	delay(2000); // Wait for serial to initialize	
  
	LedBlink_Init();
	//setupWire();
	//startWireScanner(5000, 1);
	//loopWireScanner(); // Scan for I2C devices
	//stopWire();

	setupMPU6500();
	setupBMP280();
	setupQMC5883LCompass();

	imuTimer.begin(500, 0); // Start the timer with a 1-second interval and infinite count

	Serial.println("STM32F103 Test");
}

void loop() {
	loopQueryIMU();
	LedBlink_Toggle();
	loopPWM();
}

void loopQueryIMU() {
	if(imuTimer.getState() == TimerTrigger::TIMER_OFF || !imuTimer.checkAndStep()) {
		return;
	}

	std::list<String> msgList;

	uint32_t currentTime = millis();

	String msg = "T(ms):" + String(millis());
	msgList.push_back(msg);
	//String msgAll = msg;
	//Serial.print(msg);

	dumpMPU6500(msg);
	msgList.push_back(msg);
	//msgAll += msg + "\n";
	//Serial.println(msg);

	dumpBMP280(msg);
	msgList.push_back(msg);
	//msgAll += msg + "\n";
	//Serial.println(msg);

	dumpQMC5883LCompass(msg);
	msg += "\n----\n";
	msgList.push_back(msg);
	//msgAll += msg;
	//Serial.print(msg);

	currentTime = millis() - currentTime;
	msg = "Query Time (ms): " + String(currentTime) + " ms\n";
	msgList.push_back(msg);
	
	for (const auto& m : msgList) {
		Serial.print(m);
	}
}
