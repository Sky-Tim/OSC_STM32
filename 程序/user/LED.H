#ifndef __LED_H
#define __LED_H

#include "bitband.h"
#include "stm32f10x.h"

#define BOARD_LED1 PEout(0)
#define BOARD_LED2 PEout(2)
#define DAC_LED PEout(4)
#define BEEP PEout(5)

void LED_GPIO_Config(void);

#endif

