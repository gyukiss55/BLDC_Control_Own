
#include <Arduino.h>
#include "BMP280_PressureSensor.h"
#include "MPU6500_WESensor.h"
#include "WireCustom.h"
#include "QMC5883LInterface.h"
#include "UART9600.h"
#include "jsonDump.h"
#include "Pico_UDPserver.h"

void setup() {
	Serial.begin(115200);
	//while (!Serial)
		//delay(10);
	delay(2000);

	Serial.println("setup UART1 9600");
	setupUART9600();

	setupUDPClient();

	delay(2000);
	Serial.println("MPU6500 GY-91 Scan I2C Bus started");

	setupWire(4,5);
	//while (Serial.available() == 0) {
		scanWire();
		delay(1000);
	//}
    endWire();
	Serial.println("MPU6500 GY-91 Scan I2C Bus completed");
	delay(2000);

	Serial.println("MPU6500 GY-91 Sensor Data Example");
	// Initialize the sensors
	setupBMP280PressureSensor();
	setupMPU6500_WESensor();

	PicoQMC5883L_Init();
	PicoQMC5883L_Calibration();
	PicoQMC5883L_Smoothing();
}

void loop() {
	// Read and print the sensor data
	loopUART9600();
	//loopUDPClient(8888);
	String packetStr = "";
	static unsigned long lastTimePackage = 0;
	unsigned long lastTS = getLastUART2Msg(packetStr);
	if (lastTS > lastTimePackage) {
		lastTimePackage = lastTS;
		sendUDPMessage(packetStr);
	}


	static unsigned long lastTime = 0;
	const unsigned long deltaTime = 1000; // 1 second
	unsigned long currentTime = millis();
	if (currentTime - lastTime < deltaTime) {
		return; // Skip this loop iteration if less than 2 seconds have passed
	}
	lastTime += deltaTime;

	String jsonStr = "";

	jsonDump("TsMs", (int)currentTime, jsonStr);
	jsonDumpBMP280PressureSensor(jsonStr);
	jsonDumpMPU6500_WESensor(jsonStr);
	jsonDumpQMC5883L(jsonStr);

	Serial.println(jsonStr);

	sendUDPMessage(jsonStr);

	Serial.println("**** IMU started *****");

	loopBMP280PressureSensor();
	loopMPU6500_WESensor();

	PicoQMC5883L_DumpDirection();
	
	Serial.println("**** IMU finished *****");


}

