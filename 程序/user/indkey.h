#ifndef __INDKEY_H
#define __INDKEY_H

#include "stm32f10x.h"

#define KEY_PRESSED 0  //根据上下拉电阻不同而变
#define KEY_UNPRESS	1  //根据上下拉电阻不同而变

unsigned char Key_Scan(GPIO_TypeDef* GPIOx,unsigned short int GPIO_Pin);
void Key_EXTI_Config(void);

#endif
