// BLDCData.h
#include <Arduino.h>


#define BUFFER_SIZE 32

// Volatile global parameters
extern volatile int vol_m_control;  // 0-Stop, 1-Async, 2-Listening, 3-Sync
extern volatile int vol_ti_ix_rd;      // Timer index read
extern volatile int vol_ti_ix_wr;      // Timer index wri
extern volatile uint32_t vol_ti_ts[BUFFER_SIZE];  // Timer timestamps
extern volatile uint16_t vol_ti_BLDC[BUFFER_SIZE]; // BLDC states (note: byte array)
extern volatile int vol_ei_ix;      // External interrupt index
extern volatile uint32_t vol_ei_ts[BUFFER_SIZE];  // EI timestamps micros
extern volatile int vol_ei_inp[BUFFER_SIZE];     // EI inputs PA0,PA1,PA2 status

extern int periodMS;
extern int pulseMS;
extern int periodMSPrev;
extern int pulseMSPrev;

extern uint32_t numFillBLDC;
extern uint32_t numTimerIntChangeBLDC;
extern uint32_t numExtIntChangeBLDC;
