// BLDCControl.cpp
#include "BLDCControl.h"
#include "BLDCData.h"
#include "BLDCPort.h"

/*
void BLDCControlLoop()
{
	if (vol_m_control == 1) { // Async mode
		uint32_t ts = micros();
		if (ts - vol_ti_ts[vol_ti_ix_wr] >= periodMS * 1000) {
			// Time to add next BLDC state change
			int nextIndex = (vol_ti_ix_wr + 1) % BUFFER_SIZE;
			if (nextIndex != vol_ti_ix_rd) { // Ensure buffer not full
				vol_ti_ts[vol_ti_ix_wr] = ts;
				vol_ti_BLDC[vol_ti_ix_wr] = getBLDCState(numFillBLDC);
				vol_ti_ix_wr = nextIndex;
				numFillBLDC++;
			}
		}
	}
}*/

uint16_t getBLDCState(int step)
{
    uint16_t state = 0;
    // 6-step commutation sequence for BLDC control
    switch (step % 6) {
    case 0: state = BLDC_MASKAHBL; break; // A high, B low
    case 1: state = BLDC_MASKAHCL; break; // A high, C low
    case 2: state = BLDC_MASKBHCL; break; // B high, C low
    case 3: state = BLDC_MASKBHAL; break; // B high, A low
    case 4: state = BLDC_MASKCHAL; break; // C high, A low
    case 5: state = BLDC_MASKCHBL; break; // C high, B low
    }
    return state;
}

int fillBLDCSequence(int indexStart, uint32_t tsStart, uint32_t gap, uint32_t pulse)
{
    int j = indexStart;
    for (int i = 0; i < 6; i++) {
        j = (indexStart + i) % BUFFER_SIZE;
        tsStart += gap;
        vol_ti_ts[j] = tsStart;
        vol_ti_BLDC[j] = 0; // Clear state first

        j = (j + 1) % BUFFER_SIZE;
        tsStart += gap;
        vol_ti_ts[j] = tsStart;
        vol_ti_BLDC[j] = getBLDCState(i);

        j = (j + 1) % BUFFER_SIZE;
        tsStart += pulse;
        vol_ti_ts[j] = tsStart;
        vol_ti_BLDC[j] = 0;
    }
    return (j + 1) % BUFFER_SIZE;
}

void BLDCControlLoop()
{
    if (pulseMS <= 0 || pulseMS > periodMS)
        return; // No pulse, skip control
    periodMSPrev = periodMS;
    pulseMSPrev = pulseMS;
    int indexStart = vol_ti_ix_wr;
    int indexEnd = vol_ti_ix_rd;
    if (indexEnd <= indexStart)
        indexEnd += BUFFER_SIZE; // Handle wrap-around
    if (indexEnd - indexStart < 6 * 3)
        return;
    uint32_t lastTS = 0;
    if (indexStart != indexEnd) {
        lastTS = vol_ti_ts[(indexEnd + BUFFER_SIZE - 1) % BUFFER_SIZE];
    }

    uint32_t nowTS = micros();
    if (nowTS > lastTS) {
        lastTS = nowTS;
    }
    vol_ti_ix_wr = fillBLDCSequence(indexStart, lastTS, pulseMS * 1000, (periodMS - pulseMS) * (1000 / 2));
    numFillBLDC++;

}

