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

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting the I2C interface.");
  Wire.setPins(19, 22); // SDA, SCL
  Wire.begin();
  scanWire();
  compassPtr = new QMC5883LCompass();
  QMC5883LCompass& compass = *compassPtr;
  compass.init();
  
}

void loop() {
  int a;
  QMC5883LCompass& compass = *compassPtr;
  
  // Read compass values
  compass.read();

  // Return Azimuth reading
  a = compass.getAzimuth();
  
  Serial.print("A: ");
  Serial.print(a);
  Serial.println();
  
  delay(250);
}

void scanWire ()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
	// The i2c_scanner uses the return value of
	// the Write.endTransmisstion to see if
	// a device did acknowledge to the address.
	Wire.beginTransmission(address);
	error = Wire.endTransmission();
	if (error == 0)
	{
	  Serial.print("I2C device found at address 0x");
	  if (address<16)
		Serial.print("0");
	  Serial.print(address,HEX);
	  Serial.println("  !");
	  nDevices++;
	}
	else if (error==4)
	{
	  Serial.print("Unknown error at address 0x");
	  if (address<16)
		Serial.print("0");
	  Serial.println(address,HEX);
	}
  }
  if (nDevices == 0)
	Serial.println("No I2C devices found\n");
  else
	Serial.println("done\n");
}
