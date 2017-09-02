#ifndef __PINCFG_H_
#define __PINCFG_H_

#include "bitband.h"
#include "stm32f10x.h"

#define BOARD_LED1 PEout(0)
#define BOARD_LED2 PEout(2)
#define DAC_LED PEout(4)
#define BEEP PEout(5)
#define JDQ_ACDC PGout(5)
#define JDQ_AV PGout(3)
#define CD4051A PBout(12)
#define CD4051B PBout(14)
#define CD4051C PDout(12)
#define KEY1 PBin(10)
#define KEY2 PBin(11)

void PinCfg_SWITCH(void);
void PinCfg_JDQ(void);
void PinCfg_CD4051(void);
void PinCfg_KEY(void);
void PinCfg(void);
void PinCfg_Beep(unsigned char times);

#endif
