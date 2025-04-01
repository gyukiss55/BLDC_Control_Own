
// STMTimer.cpp

#include <Arduino.h>
#include <HardwareTimer.h>
#include "STMTimer.h"


TIM_TypeDef* Instance3 = TIM3;
TIM_TypeDef* Instance4 = TIM4;
HardwareTimer* Timer3 = new HardwareTimer(Instance3);
HardwareTimer* Timer4 = new HardwareTimer(Instance4);

volatile uint32_t timer4IntCounter = 0;
volatile uint32_t timer3IntCounter = 0;
volatile uint32_t extIntCounter = 0;

volatile bool b8State = false;
volatile bool b9State = false;
volatile bool b12State = false;
volatile bool b13State = false;
volatile bool b14State = false;
volatile bool b15State = false;

volatile bool b11State = false; //debug signal state

volatile uint8_t blcdStatus = 0; // 0 - off, 1 - 8,11 on, 2 - 8,13 on, 3 - 10,13 on, 4 - 10,9 on, 5 - 12,9 on, 6 - 12,11 on

uint32_t duty = 0;

void Clear6Output()
{
    digitalWrite(PB8, LOW);
    digitalWrite(PB9, LOW);
    digitalWrite(PB12, LOW);
    digitalWrite(PB13, LOW);
    digitalWrite(PB14, LOW);
	digitalWrite(PB15, LOW);
}

void Clear6OutputStatus()
{
    b8State = false;
    b9State = false;
    b12State = false;
    b13State = false;
    b14State = false;
    b15State = false;
}


void Timer4Callback()
{
    timer4IntCounter++; // Minimal ISR to avoid delays
    Clear6Output();
	if (b8State) {
		digitalWrite(PB8, HIGH);
	}
    if (b9State) {
        digitalWrite(PB9, HIGH);
    }
    if (b12State) {
        digitalWrite(PB12, HIGH);
    }
    if (b13State) {
        digitalWrite(PB13, HIGH);
    }
    if (b14State) {
        digitalWrite(PB14, HIGH);
    }
    if (b15State) {
        digitalWrite(PB15, HIGH);
    }

}

void Timer3Callback()
{
    timer3IntCounter++; // Minimal ISR to avoid delays
	Clear6OutputStatus();
    Clear6Output();

	//b11State = !b11State; // debug signal
	//if (b11State)
	//	digitalWrite(PB11, HIGH);
 //   else
 //       digitalWrite(PB11, LOW);


	blcdStatus++;
	if (blcdStatus > 6) {
		blcdStatus = 1;
	}

	switch (blcdStatus) {
    case 1:
		b8State = true;
		b13State = true;
        break;
    case 2:
        b8State = true;
        b15State = true;
        break;
    case 3:
        b12State = true;
        b15State = true;
        break;
    case 4:
        b12State = true;
        b9State = true;
        break;
    case 5:
        b14State = true;
        b9State = true;
		break;
    case 6:
        b14State = true;
        b13State = true;
        break;
    }
}

void SetupTimer4()
{
    Timer4->setPWM(2, PB7, 20000, duty); // Channel 2, 20 kHz, 50% duty
    Timer4->attachInterrupt(Timer4Callback);
}

void SetupTimer3()
{
    Timer3->setPWM(1, PA6, 2000, 50); // Channel 1, 2000 Hz, 50% duty
    Timer3->attachInterrupt(Timer3Callback);
}

void SetupDigitalIO()
{
	pinMode(PB6, INPUT); // External interrupt

    //pinMode(PB11, OUTPUT); // debug signal

	pinMode(PB8, OUTPUT);
	pinMode(PB9, OUTPUT);
	pinMode(PB12, OUTPUT);
    pinMode(PB13, OUTPUT);
    pinMode(PB14, OUTPUT);
    pinMode(PB15, OUTPUT);
    Clear6Output ();
}

void ExternalInterruptHandler()
{
	extIntCounter++;
    Clear6Output();
}

void SetupExternalInterrupt()
{
    pinMode(PB6, INPUT_PULLUP); // Enable pull-up resistor if needed
    attachInterrupt(digitalPinToInterrupt(PB6), ExternalInterruptHandler, FALLING);
}

void SetDutyAndPeriod(uint32_t dutyIn, uint32_t period)
{
    uint32_t dutyClk = map(dutyIn, 0, 100, 0, 3600);
	duty = dutyIn;
	Timer4->setCaptureCompare(2, duty);
	Timer3->setPWM(1, PA6, period, 50); // Channel 1, 2000 Hz, 50% duty
}


void LoopTimer4Duty()
{
    static uint32_t lastTsDuty = 0;
    uint32_t currentTs = millis();
    if (currentTs - lastTsDuty > 100) {
        lastTsDuty = currentTs;
        //duty += 25;
        //if (duty >= 3600)
        //    duty = 0;
        //Timer4->setCaptureCompare(2, duty);

    }

    static uint32_t lastTsSerail = 0;
    static uint32_t timer4IntCounterPrev = 0;
    static uint32_t timer3IntCounterPrev = 0;
    static uint32_t extIntCounterPrev = 0;

    if (currentTs - lastTsSerail > 1000) {
        lastTsSerail = currentTs;
        Serial.print(currentTs);
        Serial.print("- duty:");
        Serial.print(duty);

        Serial.print(" tim4_cnt:");
        uint32_t timer4IntCounterLocal = timer4IntCounter;
        Serial.print(timer4IntCounterLocal - timer4IntCounterPrev);
        timer4IntCounterPrev = timer4IntCounterLocal;

        Serial.print(" tim3_cnt:");
        uint32_t timer3IntCounterLocal = timer3IntCounter;
        Serial.print(timer3IntCounterLocal - timer3IntCounterPrev);
        timer3IntCounterPrev = timer3IntCounterLocal;

        Serial.print(" ext_cnt:");
        uint32_t extIntCounterLocal = extIntCounter;
        Serial.print(extIntCounterLocal - extIntCounterPrev);
        extIntCounterPrev = extIntCounterLocal;

        Serial.println(" ");

    }
}

void SerialInputHandling()
{
    if (Serial.available() > 0) { //Check if data is available in the serial buffer
        String data = Serial.readStringUntil('\n'); //Read the data until a newline character
        Serial.print("You entered: ");
        Serial.println(data);
        for (int i = 0; i < 1; i++) {
            if (toupper(data[0]) != 'D') {
                Serial.println("ERROR: No 'D'!");
				break;
            }


            int p1 = data.indexOf(',');
            if (p1 >= data.length()) {
				Serial.print("ERROR: p1 >= data.length()!");
				Serial.print(" p1=");
				Serial.print(p1);
				Serial.print(" data.length()=");
				Serial.println(data.length());
				break;
            }
			String num1Str = data.substring(1, p1);
            Serial.print("num1Str:");
            Serial.println(num1Str);

			String data2 = data.substring(p1 + 1);
            Serial.print("data2:");
            Serial.println(data2);
            if (toupper(data2[0]) != 'P') {
                Serial.println("ERROR: No 'P'!");
                break;
            }
            int p2 = data2.indexOf(';');
            if (p2 >= data2.length()) {
                Serial.print("ERROR: p2 >= data2.length()!");
                Serial.print(" p2=");
                Serial.print(p2);
                Serial.print(" data2.length()=");
                Serial.println(data2.length());
                break;
            }

			String num2Str = data2.substring(1, p2);

			int num1 = num1Str.toInt();
			int num2 = num2Str.toInt();
			    
			if (num1 >= 0 && num2 > 10  && num1 < 3650) {
				//Timer4->setCaptureCompare(2, num1);
				
                //Timer3->setPWM(1, PA6, num2, 50); // Channel 1, 2000 Hz, 50% duty
                //Timer3->attachInterrupt(Timer3Callback);
				Serial.print("Set duty:");
				Serial.print(num1);
				Serial.print(", period:");
				Serial.print(num2);
                Serial.println(" Hz");
				SetDutyAndPeriod(num1, num2);
				return;
			}
            Serial.print("ERROR: (num1 >= 0 && num2 > 10  && num1 < 100)!");
            Serial.print(" num1=");
            Serial.print(num1);
            Serial.print(" num2=");
            Serial.println(num2);
        }
        Serial.println("Usage: 'Dxx,Pyyyyy;'");
     }
}