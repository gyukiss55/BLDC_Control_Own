// pwmOutput.h
#ifndef PWM_OUTPUT_H
#define PWM_OUTPUT_H

void setupPWMOutput();
void loopPWMOutput();
void parseCommand();
void setValue(uint8_t channel, uint16_t value);

#endif