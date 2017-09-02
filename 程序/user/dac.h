#ifndef __DAC_H
#define __DAC_H

void DAC_Config(void);
void Set_DAC_Value(unsigned int vol);
void DACTriggerByTIM2(unsigned short int Auto_Reload,unsigned short int Clock_Div);

#endif
