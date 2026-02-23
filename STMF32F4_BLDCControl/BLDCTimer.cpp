// BLDCTimer.cpp
#include <Arduino.h>

#include "BLDCTimer.h"
#include "BLDCData.h"
#include "BLDCPort.h"

HardwareTimer* MyTim = NULL;

uint32_t maxDeltaMS = 0;

void TimerHandler(void) {
// Process timer event at vol_ti_ix_rd index

    if (vol_ti_ix_rd != vol_ti_ix_wr) {
        uint32_t ts = micros();
        if (ts >= vol_ti_ts[vol_ti_ix_rd]) {

            digitalWrite(BLDC_PINTT, HIGH);

            uint16_t bldcState = vol_ti_BLDC[vol_ti_ix_rd];
            GPIOB->ODR = (GPIOB->ODR & ~BLDC_MASK) | (bldcState & BLDC_MASK);
            vol_ti_ix_rd = (vol_ti_ix_rd + 1) % BUFFER_SIZE;
            numTimerIntChangeBLDC++;

            digitalWrite(BLDC_PINTT, LOW);

        }
    }
}

void TimerHandlerFunction(void) {
	uint32_t now = micros();
    if (vol_ti_ix_rd != vol_ti_ix_wr) {
        uint32_t ts = micros();
        // Process timer event at vol_ti_ix_rd index
        if (ts >= vol_ti_ts[vol_ti_ix_rd]) {
            uint16_t bldcState = vol_ti_BLDC[vol_ti_ix_rd];
            GPIOB->ODR = (GPIOB->ODR & ~BLDC_MASK) | (bldcState & BLDC_MASK);
            /*
            switch(bldcState) {
                case BLDC_MASKAHBL:
                    digitalWrite(BLDC_PINAH, HIGH);
                    digitalWrite(BLDC_PINBL, HIGH);

                    Serial.print(vol_ti_ix_rd);
					Serial.printf("-AHBL\n");

                    break;
                case BLDC_MASKAHCL:
                    digitalWrite(BLDC_PINAH, HIGH);
                    digitalWrite(BLDC_PINCL, HIGH);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-AHCL\n");

                    break;
                case BLDC_MASKBHCL:
                    digitalWrite(BLDC_PINBH, HIGH);
                    digitalWrite(BLDC_PINCL, HIGH);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-BHCL\n");

                    break;
                case BLDC_MASKBHAL:
                    digitalWrite(BLDC_PINBH, HIGH);
                    digitalWrite(BLDC_PINAL, HIGH);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-BHAL\n");

                    break;
                case BLDC_MASKCHAL:
                    digitalWrite(BLDC_PINCH, HIGH);
                    digitalWrite(BLDC_PINAL, HIGH);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-CHAL\n");

                    break;
                case BLDC_MASKCHBL:
                    digitalWrite(BLDC_PINCH, HIGH);
                    digitalWrite(BLDC_PINBL, HIGH);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-CHBL\n");

                    break;
				case 0:
                    digitalWrite(BLDC_PINAH, LOW);
                    digitalWrite(BLDC_PINAL, LOW);
                    digitalWrite(BLDC_PINBH, LOW);
                    digitalWrite(BLDC_PINBL, LOW);
                    digitalWrite(BLDC_PINCH, LOW);
                    digitalWrite(BLDC_PINCL, LOW);

                    Serial.print(vol_ti_ix_rd);
                    Serial.printf("-0\n");

					break;

                default:
                    Serial.print(vol_ti_ix_rd);
					Serial.print("-Unknown BLDC state:");
                    Serial.println(bldcState);

					break;
            }
            */
            vol_ti_ix_rd = (vol_ti_ix_rd + 1) % BUFFER_SIZE;
            numTimerIntChangeBLDC++;
                
        }
    }
    uint32_t now2 = micros();
    if (now2 - now > maxDeltaMS)
    {
        maxDeltaMS = now2 - now;
        Serial.printf("Max timer handler duration: %d us\n", maxDeltaMS);
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

void loopTimerFunction()
{
    //TimerHandlerFunction();
}
