#include "STMTimer.h"

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("STM32F4xx-PWM B7 (50)");

  SetupTimer4 ();
  SetupTimer3 (); 
  SetupExternalInterrupt ();
  SetupDigitalIO();
}

void loop ()
{

  LoopTimer4Duty ();
  SerialInputHandling ();

}


