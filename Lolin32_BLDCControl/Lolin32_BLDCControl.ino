#include <Arduino.h>
#include "BLDCWebServer.h"
#include "BLDCControl.h"
#include "BLDCSerial.h"




// ---------------- SETUP ----------------
void setup()
{
    setupSerial();

    setupBLDCControl();

    //setupWebServer();
    Serial.println("BLDC Control Setup complete. #V1.0.");
}

// ---------------- LOOP ----------------
void loop()
{
    //loopBLDCControl();
    //loopWebServer();
    loopSerial();
}
