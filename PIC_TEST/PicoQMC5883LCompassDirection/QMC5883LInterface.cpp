// This file is part of the PicoQMC5883L library

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

#include <Arduino.h>
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void PicoQMC5883L_Init() {
	Wire.setSDA(20);
	Wire.setSCL(21);
	Wire.begin();
	compass.setADDR(0x0D);
	compass.init();
}

void PicoQMC5883L_Calibration() {

	Serial.println("This will provide calibration settings for your QMC5883L chip. When prompted, move the magnetometer in all directions until the calibration is complete.");
	Serial.println("Calibration will begin in 5 seconds.");
	delay(5000);

	Serial.println("CALIBRATING. Keep moving your sensor...");
	compass.calibrate();

	Serial.println("DONE. Copy the lines below and paste it into your projects sketch.);");
	Serial.println();
	Serial.print("compass.setCalibrationOffsets(");
	Serial.print(compass.getCalibrationOffset(0));
	Serial.print(", ");
	Serial.print(compass.getCalibrationOffset(1));
	Serial.print(", ");
	Serial.print(compass.getCalibrationOffset(2));
	Serial.println(");");
	Serial.print("compass.setCalibrationScales(");
	Serial.print(compass.getCalibrationScale(0));
	Serial.print(", ");
	Serial.print(compass.getCalibrationScale(1));
	Serial.print(", ");
	Serial.print(compass.getCalibrationScale(2));
	Serial.println(");");
}

void PicoQMC5883L_Smoothing(int step, bool advanced) {
/*
   *   call setSmoothing(STEPS, ADVANCED);
   *
   *   STEPS     = int   The number of steps to smooth the results by. Valid 1 to 10.
   *                     Higher steps equals more smoothing but longer process time.
   *
   *   ADVANCED  = bool  Turn advanced smmothing on or off. True will remove the max and min values from each step and then process as normal.
   *                     Turning this feature on will results in even more smoothing but will take longer to process.
   *
   */
	compass.setSmoothing(step, advanced);
}

void PicoQMC5883L_DumpDirection() {
	int x, y, z;

	compass.read();

	x = compass.getX();
	y = compass.getY();
	z = compass.getZ();

	Serial.print("X: ");
	Serial.print(x);
	Serial.print(" Y: ");
	Serial.print(y);
	Serial.print(" Z: ");
	Serial.print(z);
	Serial.println();

	byte a = compass.getAzimuth();
	byte b = compass.getBearing(a);

	Serial.print("A: ");
	Serial.print(a);

	Serial.print("  B: ");
	Serial.print(b);

	Serial.println();

	char myArray[3];
	compass.getDirection(myArray, a);

	Serial.print(myArray[0]);
	Serial.print(myArray[1]);
	Serial.print(myArray[2]);
	Serial.println();
	Serial.println();
}
