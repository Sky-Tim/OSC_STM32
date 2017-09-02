#ifndef __TFT_DRIVE_H
#define __TFT_DRIVE_H

#include "tft_api.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR


void LCD1963_Init(void);
void FSMC_LCD_Init(void);
unsigned short LCD_RD_data(void);
void LCD_WR_CMD(unsigned int index,unsigned int val);
void LCD_WR_Data(unsigned int val);
void LCD_WR_Data_8(unsigned int val);
void LCD_WR_REG(unsigned int index);

#endif
