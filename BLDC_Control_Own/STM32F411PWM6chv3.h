// STM32F411PWM6chv3.h
#include "system_stm32f4xx.h"

#if defined(STM32F411xE)
  // This is an STM32F411 device
  //#pragma message "Compiling for STM32F411xE"
  //#ifndef (_STM32F411PWM6CHV3_)
  #define _STM32F411PWM6CHV3_
  //#endif
#elif defined(STM32F401xC)
  // This is an STM32F401 variant
  //#pragma message "Compiling for STM32F401xC"
  //#ifndef (_STM32F411PWM6CHV3_)
  #define _STM32F411PWM6CHV3_
  //#endif
#endif

#if defined (_STM32F411PWM6CHV3_)
void setupSTM32F411PWM6chv3();
void loopSTM32F411PWM6chv3();
void SystemClock_ConfigSTM32F411PWM6chv3(void);
void GPIO_InitSTM32F411PWM6chv3(void);
void TIM1_PWM_InitSTM32F411PWM6chv3(void);
#endif // _STM32F411PWM6CHV3_

void setupPWM3V1();
void loopPWM3V1();
