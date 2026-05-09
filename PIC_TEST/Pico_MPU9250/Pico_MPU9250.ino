/**
 @file read9axis.ino
 @brief This is an Example for the FaBo 9Axis I2C Brick.

   http://fabo.io/202.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include <Wire.h>
#include <FaBo9Axis_MPU9250.h>

FaBo9Axis fabo_9axis;

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10);

    Wire.setSDA(20);
    Wire.setSCL(21);
    Wire.begin();

    scanWire ();
  
    Serial.println("configuring device.");

    if (fabo_9axis.begin()) {
        Serial.println("configured FaBo 9Axis I2C Brick");
    } else {
        Serial.println("device error");
        while(1);
    }
}

void loop() {
  float ax,ay,az;
  float gx,gy,gz;
  float mx,my,mz;
  float temp;

  fabo_9axis.readAccelXYZ(&ax,&ay,&az);
  fabo_9axis.readGyroXYZ(&gx,&gy,&gz);
  fabo_9axis.readMagnetXYZ(&mx,&my,&mz);
  fabo_9axis.readTemperature(&temp);

  Serial.print("ax: ");
  Serial.print(ax);
  Serial.print(" ay: ");
  Serial.print(ay);
  Serial.print(" az: ");
  Serial.println(az);

  Serial.print("gx: ");
  Serial.print(gx);
  Serial.print(" gy: ");
  Serial.print(gy);
  Serial.print(" gz: ");
  Serial.println(gz);

  Serial.print("mx: ");
  Serial.print(mx);
  Serial.print(" my: ");
  Serial.print(my);
  Serial.print(" mz: ");
  Serial.println(mz);

  Serial.print("temp: ");
  Serial.println(temp);

  delay(1000);
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
