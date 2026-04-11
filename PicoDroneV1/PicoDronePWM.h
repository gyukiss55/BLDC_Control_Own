// PicoDronePWM.h
#ifndef PICODRONEPWM_H
#define PICODRONEPWM_H

#include <Arduino.h>

void PicoDronePWM_init();
void PicoDronePWM_set(int ch, uint16_t pulse_us);
uint16_t PicoDronePWM_get(int ch);

#endif // !PICODRONEPWM_H
