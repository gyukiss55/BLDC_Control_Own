// BLDCControl.h
#include <Arduino.h>

void setupBLDCControl();

int getDriveCycleCounter();
uint32_t getExtIntCounter();
uint32_t getPWMDuty();
uint32_t getBLDCPeriod();
void setPWMDuty(uint32_t duty);
void setBLDCPeriod(uint32_t period);