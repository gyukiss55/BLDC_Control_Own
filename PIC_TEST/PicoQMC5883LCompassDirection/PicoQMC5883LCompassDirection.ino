/*
===============================================================================================================
QMC5883LCompass.h Library Direction Example Sketch
Learn more at [https://github.com/mprograms/QMC5883Compas]

This example shows how to get Compass direction.

===============================================================================================================
Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/

//PicoQMC5883LCompass

#include "QMC5883LInterface.h"
#include "WireCustom.h"


void setup() {
	Serial.begin(115200);
	while (!Serial)
		delay(10);

	delay(2000);
	Serial.println("Wire Test begin");
	setupWire(0,0);
	scanWire();
	endWire();
	Serial.println("Wire Test end");
	delay(2000);

	PicoQMC5883L_Init();
	PicoQMC5883L_Calibration();
	PicoQMC5883L_Smoothing(10,true);
	Serial.println("QMC5883P Test");
}

void loop() {
	PicoQMC5883L_DumpDirection();
  
	delay(500);
}
