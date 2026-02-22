// BLDCTimer.cpp
#include <Arduino.h>

#include "BLDCTimer.h"
#include "BLDCData.h"
#include "BLDCPort.h"

HardwareTimer* MyTim = NULL;

void TimerHandler(void) {
    if (vol_ti_ix_rd != vol_ti_ix_wr) {
        uint32_t ts = micros();
        // Process timer event at vol_ti_ix_rd index
        if (ts >= vol_ti_ts[vol_ti_ix_rd]) {
            // Timer event due, process it
            uint16_t bldcState = vol_ti_BLDC[vol_ti_ix_rd];
            digitalWrite(BLDC_PINAH, LOW);
            digitalWrite(BLDC_PINAL, LOW);
            digitalWrite(BLDC_PINBH, LOW);
            digitalWrite(BLDC_PINBL, LOW);
            digitalWrite(BLDC_PINCH, LOW);
            digitalWrite(BLDC_PINCL, LOW);
            switch(bldcState) {
                case BLDC_MASKAHBL:
                    digitalWrite(BLDC_PINAH, HIGH);
                    digitalWrite(BLDC_PINBL, HIGH);
                    break;
                case BLDC_MASKAHCL:
                    digitalWrite(BLDC_PINAH, HIGH);
                    digitalWrite(BLDC_PINCL, HIGH);
                    break;
                case BLDC_MASKBHCL:
                    digitalWrite(BLDC_PINBH, HIGH);
                    digitalWrite(BLDC_PINCL, HIGH);
                    break;
                case BLDC_MASKBHAL:
                    digitalWrite(BLDC_PINBH, HIGH);
                    digitalWrite(BLDC_PINAL, HIGH);
                    break;
                case BLDC_MASKCHAL:
                    digitalWrite(BLDC_PINCH, HIGH);
                    digitalWrite(BLDC_PINAL, HIGH);
                    break;
                case BLDC_MASKCHBL:
                    digitalWrite(BLDC_PINCH, HIGH);
                    digitalWrite(BLDC_PINBL, HIGH);
                    break;
            }
            //GPIOB->ODR = (GPIOB->ODR & ~BLDC_MASK) | (bldcState & BLDC_MASK);
            vol_ti_ix_rd = (vol_ti_ix_rd + 1) % BUFFER_SIZE;
            numTimerIntChangeBLDC++;
            /*
            if (bldcState & BLDC_MASKAH) {
                digitalWrite(PB12, HIGH);

            }
            else
            {
                digitalWrite(PB12, LOW);
            }
            */

        }
    }
}

void setupTimer()
{
    // Timer interrupt 10us period [web:16][web:13]
    // STM32F411 100MHz sysclk, timer x2 -> 200MHz, prescaler=1 (0), period=1999 (~10us)
    MyTim = new HardwareTimer(TIM2);
    MyTim->setOverflow(1999, TICK_FORMAT);  // 200MHz / 2000 = 100kHz = 10us
    MyTim->attachInterrupt(TimerHandler);
    MyTim->resume();
}
