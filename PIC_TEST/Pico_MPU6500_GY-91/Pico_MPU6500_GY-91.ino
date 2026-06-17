
#include <Arduino.h>
#include "BMP280_PressureSensor.h"
#include "MPU6500_WESensor.h"
#include "WireCustom.h"
#include "UART9600.h"

void setup() {
	Serial.begin(115200);
	//while (!Serial)
		//delay(10);
	delay(2000);

	Serial.println("setup uart1");
	setupUART9600();

	delay(2000);
	Serial.println("MPU6500 GY-91 Scan I2C Bus started");

	while (Serial.available() == 0) {
		setupWire(5,4);
		scanWire();
		endWire();
		//delay(1000);
	}
	Serial.println("MPU6500 GY-91 Scan I2C Bus completed");
	delay(2000);

	Serial.println("MPU6500 GY-91 Sensor Data Example");
	// Initialize the sensors
	setupBMP280PressureSensor();
	setupMPU6500_WESensor();
}

void loop() {
	// Read and print the sensor data
	loopUART9600();
	loopBMP280PressureSensor();
	loopMPU6500_WESensor();
	delay(2000); // Delay for 1 second before the next reading
}

