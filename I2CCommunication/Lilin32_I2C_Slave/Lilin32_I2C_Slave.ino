#include <Wire.h>

#define PIN_SDA 18
#define PIN_SCL 19
//#define PIN_SDA 25
//#define PIN_SCL 26

#define SLAVE_ADDR 0x40

#define I2C_CLK 100000

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
  Wire.begin(SLAVE_ADDR, PIN_SDA, PIN_SCL, I2C_CLK);   // SDA=GPIO16, SCL=GPIO17
  Wire.onReceive(receiveEvent);
}

void loop()
{
  static uint32_t lastPrint = 0;
  static int ixRec = 0;

  if (millis() - lastPrint > 1000)
  {
    lastPrint = millis();

    int ix = indexI2C;

    String str ="i2c-";
    String strPlt ="";
    str+= String (lastPrint) + "/";
    str+= String (receiveCounter) + ":";
  
    for (int i = 0; i < BufferSize; i++)
    {
      uint32_t v = bufferI2C[(ix - i - 1 + 2 * BufferSize) % BufferSize];

      uint16_t value = v & 0xFFFF;
      uint16_t t = (v >> 16) & 0xFFFF;

      str += String(value);
      strPlt += String(value);
      str += String("/");
      str += String(t);
      strPlt += ",";
      strPlt += String(t);
	    if (i < BufferSize - 1)
        str += String(",");
    }
    //Serial.println(str);

  }

  if (ixRec != indexI2C) {
    uint32_t v = bufferI2C[ixRec];

    uint16_t value = v & 0xFFFF;
    uint16_t t = (v >> 16) & 0xFFFF;

    String strPlt = String(value);
    strPlt += ",";
    strPlt += String(t%4000);
    strPlt += ",";
    strPlt += String(4000);
    strPlt += ",";
    strPlt += String(0);
    Serial.println(strPlt);

    ixRec = (ixRec + 1) % BufferSize;
  }
}