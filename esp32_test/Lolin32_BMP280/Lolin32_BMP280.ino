#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);

  Wire.begin(19, 22);

  scanWire();


  // BMP280 init
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  Serial.println("BMP280 initialized");

  delay(1000);
}

void loop() {

  sensors_event_t a, g, temp;

  float pressure = bmp.readPressure() / 100.0; // hPa
  float altitude = bmp.readAltitude(1013.25);

  Serial.println("==============");

  // Temperature
  Serial.print("TEMP: ");
  Serial.print(temp.temperature);
  Serial.println(" C");

  // Pressure
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // Altitude
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  delay(500);
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

