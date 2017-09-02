#ifndef LCDCONF_H
#define LCDCONF_H


#define LCD_XSIZE          (480)
#define LCD_YSIZE          (272)
#define LCD_CONTROLLER     (9320)
#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)
#define LCD_SWAP_XY        (0)
#define LCD_INIT_CONTROLLER()  LCD1963_Init();

#endif /* LCDCONF_H */

