// Perplexity
// Black Pill STM32F411CE BLDC Control Project
// Select board: Generic F411CE in Arduino IDE with STM32 core

#include "BLDCData.h"
#include "BLDCTimer.h"
#include "BLDCPort.h"
#include "BLDCExtInt.h"
#include "BLDCSerial.h"
#include "BLDCControl.h"
#include "BLDCLed.h"

void setup() {

	setupBLDCPort();

    //setupBLDCExtInt();

    //setupTimer();

    setupSerial();
}

void loop() {
    unitTest();
    //loopNormal ();
}

void unitTest()
{
    Serial.print(micros());
    Serial.println(" - unit test...");
    unitTestBLDCPort();
    //unitTestBLDCExtInt();
    //unitTestBLDCTimer();
    //unitTestSerial();
    BlinkLed();
}

void loopNormal()
{
    BLDCControlLoop();
    SerialOutputLoop();
    SerialInputLoop();

    BlinkLed();
}


