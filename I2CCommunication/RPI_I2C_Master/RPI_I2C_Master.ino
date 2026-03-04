#include <Wire.h>

#define SLAVE_ADDR 0x8F

bool findI2CAddress (int addrFind)
{

  Serial.println("I2C scan start");

  bool ret = false;

  for (uint8_t addr = 1; addr < 127; addr++)
  {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Device found at 0x");
      if (addr < 16) Serial.print("0");
      if (addr == addrFind)
        ret = true;
      Serial.println(addr, HEX);
    }
  }

  Serial.println("Scan done");
  return ret;
}

void setup()
{
  Serial.begin(115200);
  delay (1000);
  Wire.begin(21, 20);   // master SDA=GPIO21, SCL=GPIO20
  Wire.setClock(100000);
  for (int i = 0; i < 100; i++) {
    if (findI2CAddress (SLAVE_ADDR))
      break;
    delay (1000);
  }
    

}

void loop()
{
  static uint32_t lastSend = 0;

  if (millis() - lastSend >= 100)
  {
    lastSend = millis();

    uint32_t t = lastSend;

    float s = sin(2.0 * PI * (t % 1000) / 1000.0);
    uint16_t value = (uint16_t)((s + 1.0) * 2000.0);

    uint8_t buf[4];

    buf[0] = value & 0xFF;
    buf[1] = value >> 8;

    buf[2] = t & 0xFF;
    buf[3] = (t >> 8) & 0xFF;

    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(buf, 4);
    Wire.endTransmission();
  }
}