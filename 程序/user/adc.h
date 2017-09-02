#ifndef __ADC_H
#define __ADC_H

#define ADC1_DR_Address    ((unsigned int)0x40012400+0x4c)
#define SAMPDEPTH 400

void ADC1_GPIO_Init(void);
void ADC1_Mode_Config(void);
void ADC1_Init(void);
unsigned short int GetTempSensor(void);
void Earse_AD_FIFO(void);

#endif
