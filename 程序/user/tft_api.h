#ifndef __TFT_H
#define __TFT_H  

#include "tft_drive.h"

#define LCD_BUFFER_SIZE 64

#define uint8  unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int

#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0



void LCD_Write_Char(uint16 x,uint16 y,uint8 ch,uint16 Color,uint16 bColor);
void LCD_Write_Char_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor);
void LCD_Write_String(uint16 x,uint16 y,const uint8 *p,uint16 Color,uint16 bColor);
void LCD_Write_String_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor);
void LCD_Write_Bmp(uint16 x,uint16 y,uint16 lenth,uint16 wide,const uint8 *p);
uint32 Get_GBKChineseCode(const unsigned char *c);
uint32 Get_GBKSmallCode(const uint8 chn[2]);


void LCD_Clear_All(uint16 bColor);
void LCD_Clear_Select(uint16 x,uint16 y,uint16 len,uint16 wide,uint16 bColor);
void Reset_LCD(void);

void Draw_Point(uint16 x,uint16 y,uint16 Color);
uint16 Get_Point(uint16 x,uint16 y);
void Set_Cursor(uint16 x,uint16 y);
void Draw_Line(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 color);
void Draw_DottedHLine(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 color,uint16 Distance);
void Draw_DottedVLine(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 color,uint16 Distance);
void Draw_Rectangle( uint16 left,uint16 top,uint16 right,uint16 bottom,uint32 color);
void Draw_Sin(uint16 A,uint16 T,uint16 cx,uint16 py,unsigned int color);
void Draw_Circle(uint16 cx,uint16 cy,uint16 r,uint16 color,uint8 fill);
void Draw_Picture(uint16 x,uint16 y,uint8 *pic);

uint16 BGR_To_RGB(uint16 c);

#endif

