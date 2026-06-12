#include <Wire.h>

void setup()
{
    Serial.begin(115200);

    Wire.setSDA(20);
    Wire.setSCL(21);
    Wire.begin();

    Serial.println("I2C Scanner");
}

void loop()
{
    byte error, address;

    for(address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if(error == 0)
        {
            Serial.print("Found: 0x");

            if(address < 16)
                Serial.print("0");

            Serial.println(address, HEX);
        }
    }

    delay(3000);
}