// HMC_QMC5883LCompass.cpp

#include <Arduino.h>
#include <QMC5883LCompass.h>

QMC5883LCompass compass;

void setupQMC5883LCompass() {
	compass.init();
}

void setSmoothing() {

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
	compass.setSmoothing(10, true);
}

void startQMC5883LCompassCalibrate() {
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

void loopQMC5883LCompassDirection() {
	compass.read();

	byte a = compass.getAzimuth();

	char myArray[3];
	compass.getDirection(myArray, a);

	Serial.print(myArray[0]);
	Serial.print(myArray[1]);
	Serial.print(myArray[2]);
	Serial.println();

	delay(250);
}

void loopQMC5883LCompassXYZ() {
	int x,y,z;

	// Read compass values
	compass.read();

	// Return x,y,z reading
	x = compass.getX();
	y = compass.getY();
	z = compass.getZ();

	Serial.print("M: ");
	Serial.print(x);
	Serial.print(',');
	Serial.print(y);
	Serial.print(',');
	Serial.print(z);
	Serial.println();

	delay(250);
}

void loopQMC5883LCompassAzimuth() {
	int a;

	// Read compass values
	compass.read();

	// Return Azimuth reading
	a = compass.getAzimuth();

	Serial.print("A: ");
	Serial.print(a);
	Serial.println();

	delay(250);
}

void loopQMC5883LCompassBearing() {
	compass.read();

	byte a = compass.getAzimuth();
	// Output here will be a value from 0 - 15 based on the direction of the bearing / azimuth.
	byte b = compass.getBearing(a);

	Serial.print("A: ");
	Serial.print(a);
    Serial.println();
	Serial.print("B: ");
	Serial.print(b);
	Serial.println();

	delay(250);
}

void dumpQMC5883LCompass(String& message) {
	compass.read();
	int x = compass.getX();
	int y = compass.getY();
	int z = compass.getZ();
	byte a = compass.getAzimuth();
	message = "Comp:" + String(x) + "," + String(y) + "," + String(z) + ", Azimuth:" + String(a);
}
