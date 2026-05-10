#ifdef _USE_QMC5883LCompassSensor_

// QMC5883LCompassSensor.cpp
#include <Arduino.h>
#include <Wire.h>
#include "QMC5883LCompassSensor.h"

/*
===============================================================================================================
QMC5883LCompass.h Library Azimuth Example Sketch
Learn more at [https://github.com/mprograms/QMC5883Compas]
===============================================================================================================
v0.3 - June 12, 2019
Written by MRPrograms
Github: [https://github.com/mprograms/]

Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/
#include <QMC5883LCompass.h>

QMC5883LCompass* compassPtr = nullptr;

void setupQMC5883LCompass() {
	compassPtr = new QMC5883LCompass();
	QMC5883LCompass& compass = *compassPtr;
	compass.init();
}

int readQMC5883LCompassAzimuth() {
	QMC5883LCompass& compass = *compassPtr;
	// Read compass values
	compass.read();
	// Return Azimuth reading
	return compass.getAzimuth();
}

void loopQMC5883LCompass() {
	QMC5883LCompass& compass = *compassPtr;
	int a;

	// Read compass values
	compass.read();

	// Return Azimuth reading
	a = compass.getAzimuth();

	Serial.print("A: ");
	Serial.print(a);
	Serial.println();

}

#endif

