#ifndef __PWM_H
#define __PWM_H

void PWM_TIM3_CH2_Set_FreqAndDuty(unsigned short int freq,unsigned short int duty);
void PWM_TIM3_CH2_Init(unsigned short int Auto_Reload);
void PWM_TIM3_CH2_Config(unsigned short int Auto_Reload,unsigned short int Clock_Div);


#endif
