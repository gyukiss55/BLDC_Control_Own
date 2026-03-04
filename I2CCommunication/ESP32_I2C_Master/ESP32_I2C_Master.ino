#include <Wire.h>

#define SLAVE_ADDR 0x40

#define PIN_SDA 21
#define PIN_SCL 20
//#define PIN_SDA 16
//#define PIN_SCL 17

#define I2C_CLK 100000
//#define I2C_CLK 20000

bool findI2CAddress (int addrFind)
{

  Serial.println("I2C scan start");

  bool ret = false;

  byte error, address; //variable for error and I2C address

  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
      ret = true;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 

  Serial.println("Scan done");
  return ret;
}

void setup()
{
  Serial.begin(115200);
  delay (10000);
  Wire.begin(PIN_SDA, PIN_SCL);   // master SDA=GPIO21, SCL=GPIO20
  Wire.setClock(I2C_CLK);
  for (int i = 0; i < 5; i++) {
    if (findI2CAddress (SLAVE_ADDR))
      break;
    delay (1000);
  }
  delay (5000);
    

}

void loop()
{
  static uint32_t lastSend = 0;

  static int countSend = 0;

  if (millis() - lastSend >= 100)
  {
    lastSend = millis();

    uint32_t t = countSend++;

    float s = sin(2.0 * PI * (t % 307) / 307.0);
    uint16_t value = (uint16_t)((s + 1.0) * 2000.0);

    uint8_t buf[4];

    buf[0] = value & 0xFF;
    buf[1] = value >> 8;

    buf[2] = t & 0xFF;
    buf[3] = (t >> 8) & 0xFF;

    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(buf, 4);
    Wire.endTransmission();
    Serial.print(lastSend);
    Serial.println(". sned 4 bytes");
  }
}