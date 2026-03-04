#include <Wire.h>

#define I2C_ADDR 0x8F

const int BufferSize = 32;

volatile uint32_t bufferI2C[BufferSize];
volatile uint16_t indexI2C = 0;
volatile uint16_t receiveCounter = 0;

void receiveEvent(int howMany)
{
  if (howMany < 4) return;

  uint8_t b0 = Wire.read();
  uint8_t b1 = Wire.read();
  uint8_t b2 = Wire.read();
  uint8_t b3 = Wire.read();

  uint32_t packed =
      ((uint32_t)b0) |
      ((uint32_t)b1 << 8) |
      ((uint32_t)b2 << 16) |
      ((uint32_t)b3 << 24);

  bufferI2C[indexI2C] = packed;

  indexI2C = (indexI2C + 1) % BufferSize;
  
  receiveCounter++;
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(I2C_ADDR, 16, 17);   // SDA=GPIO16, SCL=GPIO17
  Wire.onReceive(receiveEvent);
}

void loop()
{
  static uint32_t lastPrint = 0;

  if (millis() - lastPrint > 1000)
  {
    lastPrint = millis();

    int ix = indexI2C;

    String str ="i2c-";
    str+= String (lastPrint) + "/";
    str+= String (receiveCounter) + ":";
  
    for (int i = 0; i < BufferSize; i++)
    {
      uint32_t v = bufferI2C[(i + ix) % BufferSize];

      uint16_t value = v & 0xFFFF;
      uint16_t t = (v >> 16) & 0xFFFF;

      str += String(value);
      str += String("/");
      str += String(t);
	  if (i < BufferSize - 1)
        str += String(",");
    }
    Serial.println(str);

  }
}