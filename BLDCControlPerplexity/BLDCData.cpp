// BLDCData.cpp
#include <Arduino.h>
#include "BLDCData.h"

// Volatile global parameters
volatile int vol_m_control = 0;  // 0-Stop, 1-Async, 2-Listening, 3-Sync
volatile int vol_ti_ix_rd = 0;      // Timer index read
volatile int vol_ti_ix_wr = 0;      // Timer index wri
volatile uint32_t vol_ti_ts[BUFFER_SIZE] = { 0 };  // Timer timestamps
volatile uint16_t vol_ti_BLDC[BUFFER_SIZE] = { 0 }; // BLDC states (note: byte array)
volatile int vol_ei_ix = 0;      // External interrupt index
volatile uint32_t vol_ei_ts[BUFFER_SIZE] = { 0 };  // EI timestamps micros
volatile int vol_ei_inp[BUFFER_SIZE] = { 0 };     // EI inputs PA0,PA1,PA2 status

int periodMS = 1000;
int pulseMS = 0;
int periodMSPrev = 1000;
int pulseMSPrev = 0;

uint32_t numFillBLDC = 0;
uint32_t numTimerIntChangeBLDC = 0;
uint32_t numExtIntChangeBLDC = 0;
