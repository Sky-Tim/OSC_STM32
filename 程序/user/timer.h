#ifndef __TIMER_H
#define __TIMER_H

#include "misc.h"

void TIM5_Set_Time(unsigned short int Auto_Reload);
void TIM5_Config(unsigned short int Period,unsigned short int Prescaler);
void TIM4_Config(unsigned short int Period,unsigned short int Prescaler);
int GetSquareWaveHightLevelTime(void);

#endif

