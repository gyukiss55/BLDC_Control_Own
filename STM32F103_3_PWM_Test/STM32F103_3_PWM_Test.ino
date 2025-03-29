#include "STMTimer.h"

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("STM32F103-PWM B7, B8, B9 (50, 20, 70)");

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


