// BLDCPort.h
#include <Arduino.h>

// BLDC pins: PB12,13,14,15,8,9 -> bits 12,13,14,15,8,9 in GPIOB->ODR
#define BLDC_MASK  ((1<<12)|(1<<13)|(1<<14)|(1<<15)|(1<<8)|(1<<9))
#define BLDC_MASKAH  (1<<12)
#define BLDC_MASKAL  (1<<13)
#define BLDC_MASKBH  (1<<14)
#define BLDC_MASKBL  (1<<15)
#define BLDC_MASKCH  (1<<8)
#define BLDC_MASKCL  (1<<9)
#define BLDC_MASKAHBL  (BLDC_MASKAH | BLDC_MASKBL)
#define BLDC_MASKAHCL  (BLDC_MASKAH | BLDC_MASKCL)
#define BLDC_MASKBHAL  (BLDC_MASKBH | BLDC_MASKAL)
#define BLDC_MASKBHCL  (BLDC_MASKBH | BLDC_MASKCL)
#define BLDC_MASKCHAL  (BLDC_MASKCH | BLDC_MASKAL)
#define BLDC_MASKCHBL  (BLDC_MASKCH | BLDC_MASKBL)

void setupBLDCPort();
