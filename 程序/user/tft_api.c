/*---------------------------------------------------------------------------------
	    					STM32 4.3TFT彩屏API v3.1

 说明: 本程序是经过四次大改的最终稳定版本,此版本完全解决了之前版本显示图形和文字的
 	   时候自动死机的问题.系统的稳定得到极大的增强,增加了3种字库,分别是ASCII字库
	   16x16国家二级字库,16x16自定义字库,可供不同情况下进行选择,方便实用.
	   从V3.0版开始把与硬件相关的驱动程序单独写成TFT_Drive.c文件,把硬件无关的应用
	   程序接口写成TFT_API.c文件,同时配套相应的头文件.使用TFT的时候只需要在main文件
	   中包含TFT_API.h 调用LCD_Init(),LCD_FSMC_Init()即可完成配置使用.
 
 时间: 2013年7月28日 							BoX编写
 
 版本: V1.0 原版驱动程序,调试通过,无API 	    2013-7-27
       V2.0 改版驱动程序,增加API,不稳定 		2013-7-28
	   V2.5 改进画圆算法,增加字符串API,不稳定 	2013-8-17
	   V3.0 改进稳定性,增加大小字库显示,稳定版  2013-8-18
	   V3.1 为了适应UCGUI的移植增加两个函数 	2014-2-09
--------------------------------------------------------------------------------*/
#include "tft_api.h"
#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

    /*选择需要的字库*/
// #include "GBK_Large.h" 	//GB2132标准二级字库包含6768个常用字
// #include "GBK_Small.h"	//GBSmall字库是自己建立的字库,小巧
 #include "ascii_font.h"	//ASCII字库文件包含西文字母,常用

unsigned char LCD_Buffer[LCD_BUFFER_SIZE]; //显示缓冲区
/*---------------------------------------------------------
	函数功能: 复位液晶屏
	函数参数: 无
--------------------------------------------------------*/
void Reset_LCD(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	Software_Delay(0xf);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
}
/*--------------------------------------------------------
 功    能：RRRRRGGGGGGBBBBB 改为 BBBBBGGGGGGRRRRR 格式
 入口参数：c      BRG 颜色值
 出口参数：RGB 颜色值
 说    明：内部函数调用
 调用方法：
-------------------------------------------------------*/
uint16 BGR_To_RGB(uint16 c)
{
  uint16  r, g, b;
  b = (c>>0)  & 0x1F;
  g = (c>>5)  & 0x3F;
  r = (c>>11) & 0x1F;
  return( (b<<11) + (g<<5) + (r<<0) );
}
/*----------------------------------------------
 功    能：选择性清屏
 入口参数：SX行起始座标,SY列起始座标,
		   Length长度,Wide宽度,bColor颜色
 调用示例：LCD_Clear_Select(0,0,480,272,Yellow)
-----------------------------------------------*/
void LCD_Clear_Select(uint16 x,uint16 y,uint16 len,uint16 wide,uint16 bColor)
{                    
    u32 w;
	LCD_WR_REG(0x002A);	
	LCD_WR_Data(x>>8);	    
	LCD_WR_Data(x);
	LCD_WR_Data((len-1)>>8);	    
	LCD_WR_Data((len-1));
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    
	LCD_WR_Data(y);
	LCD_WR_Data((wide-1)>>8);	    
	LCD_WR_Data((wide-1));
	LCD_WR_REG(0x002c);
	w= (len-x)*(wide-y);
	while(w--)
	{ 
		LCD_WR_Data(bColor);
	}
} 
/*---------------------
 功    能：全部清屏
 入口参数：bColor颜色
----------------------*/
void LCD_Clear_All(uint16 bColor)
{                    
    u32 w;
	LCD_WR_REG(0x002A);	
	LCD_WR_Data(0>>8);	    
	LCD_WR_Data(0);
	LCD_WR_Data(479>>8);	    
	LCD_WR_Data(479);
    LCD_WR_REG(0x002B);	
	LCD_WR_Data(0>>8);	    
	LCD_WR_Data(0);
	LCD_WR_Data(272>>8);	    
	LCD_WR_Data(272);
	LCD_WR_REG(0x002C);
	w= 480*272;
	while(w--)
	{ 
		LCD_WR_Data(bColor);
	}
}   
/*-------------------------------------------------------
 函数功能：在指定坐标划线
 入口参数：(X0,Y0)线起点座标,(X1,Y1)线终点坐标,color颜色
--------------------------------------------------------*/ 
void Draw_Point(uint16 x,uint16 y,uint16 Color)
{								       
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    //起始地址X
	LCD_WR_Data(x);	    			
	LCD_WR_Data((x+1)>>8);	//结束地址X
	LCD_WR_Data(x);	    			    
    LCD_WR_REG(0x002B);	
	LCD_WR_Data(y>>8);	    //起始地址Y
	LCD_WR_Data(y);	    			    
	LCD_WR_Data((y)>>8);	//结束地址Y
	LCD_WR_Data(y);	    			
	LCD_WR_REG(0x2C);
	LCD_WR_Data(Color); 	   	
} 
/*-------------------------------------------------------
 函数功能：获取指定点颜色
 入口参数：(X,Y)点座标
 编写时间: 2014-2-9
--------------------------------------------------------*/ 
uint16 Get_Point(uint16 x,uint16 y)
{								       
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002A;
	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002b; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002e; 
	
	return LCD_RD_data();	   	
}
/*-------------------------------------------------------
 函数功能：设置坐标
 入口参数：(X,Y)点座标
 编写时间: 2014-2-9
--------------------------------------------------------*/
void Set_Cursor(uint16 x,uint16 y)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002A;
  	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
  	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= y>>8; 	
  	*(__IO uint16_t *) (Bank1_LCD_D)= y&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_C)= 0x002b; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)>>8; 
  	*(__IO uint16_t *) (Bank1_LCD_D)= (271-x)&0x00ff; 
} 
/*-------------------------------------------------------
 函数功能：在指定坐标划线
 入口参数：(X0,Y0)线起点座标,(X1,Y1)线终点坐标,color颜色
--------------------------------------------------------*/
void Draw_Line(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 color)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int PointX = 0,PointY = 0;
	int incx = 0,incy = 0;
	int distance = 0,xerr = 0,yerr = 0;
	unsigned int i = 0;
	if(dx == 0)		//k=1斜率为1
	{
		PointX = X0;
		if(Y0 < Y1)
		{
			PointY = Y0;
		}
		else
		{
			PointY = Y1;
		}
		for(i = 0;i <= ((Y0<Y1) ? (Y1-Y0) : (Y0-Y1));i++)
		{
		    Draw_Point(PointX,PointY,color);
			PointY++;
		}
		return;
	}
	if(dy == 0)		//k=0斜率为0
	{
		PointY = Y0;
		if(X0 < X1)
			PointX = X0;
		else
			PointX = X1;
		for(i = 0;i <= ((X0<X1) ? (X1-X0) : (X0-X1));i++)
		{
			Draw_Point(PointX,PointY,color);
			PointX++;
		}
		return;
	}
	if(dx > 0)
		incx = 1;
	else if(dx == 0)
		incx = 0;
	else
		incx = -1;

	if(dy > 0)
		incy = 1;
	else if(dy == 0)
		incy = 0;
	else
		incy = -1;

    dx = ((X0>X1) ? (X0-X1) : (X1-X0));
    dy = ((Y0>Y1) ? (Y0-Y1) : (Y1-Y0));

    if(dx>dy) 
		distance=dx;
    else 
		distance=dy;

    PointX = X0;
    PointY = Y0;
    for(i=0;i<=distance+1;i++)
    {
    	Draw_Point(PointX,PointY,color);
        xerr += dx;
        yerr += dy;
        if(xerr>distance)
        {
            xerr -= distance;
            PointX += incx;
        }
        if(yerr>distance)
        {
            yerr -= distance;
            PointY += incy;
        }
    }
}
/*-------------------------------------------------------
 函数功能：在指定坐标画水平虚线
 入口参数：(X0,Y0)线起点座标,(X1,Y1)线终点坐标,color颜色,虚线间距distance
--------------------------------------------------------*/
void Draw_DottedHLine(u16 X0,u16 Y0,u16 X1,u16 Y1,u16 color,u16 Distance)
{
	u16 _dis,div,i,starx,endx;
	if(Y0 == Y1)
	{
		_dis = ((X0>X1) ? (X0-X1) : (X1-X0)); 
		div = _dis / Distance;
		starx = X0;
		endx  = X0 + Distance;
		for(i=0; i<div; i++)
		{
		 	Draw_Line(starx,Y0,endx,Y0,color);
			starx = endx;
			endx += Distance;
		}	
	}			
}
/*-------------------------------------------------------
 函数功能：在指定坐标划垂直虚线
 入口参数：(X0,Y0)线起点座标,(X1,Y1)线终点坐标,color颜色,虚线间距distance
--------------------------------------------------------*/
void Draw_DottedVLine(u16 X0,u16 Y0,u16 X1,u16 Y1,u16 color,u16 Distance)
{
	u16 _dis,div,i,stary,endy;
	if(X0 == X1)
	{
		_dis = ((Y0>Y1) ? (Y0-Y1) : (Y1-Y0)); 
		div = _dis / Distance;
		stary = Y0;
		endy  = Y0 + Distance;
		for(i=0; i<div; i++)
		{
		 	Draw_Line(X0,stary,X0,endy,color);
			stary = endy;
			endy += Distance;
		}	
	}			
}
/*------------------------------------
              绘制矩形框
输入参数：矩形的起始位置left,top 
          矩形的结束位置right,bottom 
 		  矩形框的颜色  color
------------------------------------*/
void Draw_Rectangle( uint16 left,uint16 top,uint16 right,uint16 bottom,uint32 color)
{
	Draw_Line(left,top,right,top,color);
	Draw_Line(left,top,left,bottom,color);
	Draw_Line(right,top,right,bottom,color);
	Draw_Line(left,bottom,right,bottom,color);
}
/*--------------------------------------
 函数功能: 绘制SIN曲线
 函数参数: y=Asin(wx+cx)  w=2pi/T,偏移量py
 调用示例: Draw_Sin(40,130,0,100,Yellow)
---------------------------------------*/
void Draw_Sin(uint16 A,uint16 T,uint16 cx,uint16 py,unsigned int color)
{	
	float PI_2 = 6.2832;
	float y;
	unsigned int x;
	for(x=0;x<=480;x++)
	{
		y = A*sin((PI_2/T)*x + cx) + py;
		Draw_Point(x,y,color);
	}
}
/*----------------------------------------
 函数功能: 对称打点法画圆
 函数参数: 圆心坐标(x,y)	圆的半径 r
		   颜色 Color       是否填充 fill
 调用示例: Draw_Circle(100,100,50,Green,0) 
----------------------------------------*/
void Draw_Circle(uint16 cx,uint16 cy,uint16 r,uint16 color,uint8 fill)
{
	uint16 x=0,y=r;
	short int delta,temp;
	
	delta = 3-(r<<1);  //3-r*2
	while(y>x)
	{
		if(fill)
		{
			Draw_Line(cx+x,cy+y,cx-x,cy+y,color);
			Draw_Line(cx+x,cy-y,cx-x,cy-y,color);
			Draw_Line(cx+y,cy+x,cx-y,cy+x,color);
			Draw_Line(cx+y,cy-x,cx-y,cy-x,color);
		}
		else
		{
			Draw_Point(cx+x,cy+y,color);
			Draw_Point(cx-x,cy+y,color);
			Draw_Point(cx+x,cy-y,color);
			Draw_Point(cx-x,cy-y,color);
			Draw_Point(cx+y,cy+x,color);
			Draw_Point(cx-y,cy+x,color);
			Draw_Point(cx+y,cy-x,color);
			Draw_Point(cx-y,cy-x,color);
		}
		x++;
		if(delta >= 0)
		{
			y--;
			temp= (x<<2); //x*4
			temp-=(y<<2); //y*4
			delta += (temp+10);
		}
		else
		{
			delta += ((x<<2)+6); //x*4 + 6
		}
	}
}
/*--------------------------------------------------
 功    能：在指定座标显示一个8x16点阵的ASCII字符
 入口参数：(x,y)坐标
           charColor  字符的颜色
           bColor    字符背景颜色
 说    明：需要包含ascii_font.h头文件才能使用
 调用示例：LCD_Write_Char(10,10,'a',Green,Black)
---------------------------------------------------*/
#ifdef ASCII_FONT 
void LCD_Write_Char(uint16 x,uint16 y,uint8 ch,uint16 Color,uint16 bColor)
{       
	#define MAX_CHAR_POSX 464
	#define MAX_CHAR_POSY 262
   	uint16 i=0,j=0;
  	uint8 temp_char = 0;      
    if(x>MAX_CHAR_POSX||y>MAX_CHAR_POSY)return;
	
  	for (i=0; i<16; i++)
  	{
	    /* ASCII_8x16字库定义在ascii_font.h中 */
	    temp_char = ASCII_8x16[ ((ch-0x20)*16)+i ];
	    for (j=0;j<8;j++)
	    {  
		   if ( (temp_char >> 7-j) & 0x01 == 0x01)
		   {
		     Draw_Point(x+j,y+i,Color); // 字符颜色
		   }
	       else
	       {
	         Draw_Point(x+j,y+i,bColor); // 背景颜色
	       }
    	}
  	}
}  	 
/*------------------------------------------------------
 描述  ：在指定坐标处显示16*16大小的指定颜色英文字符串
 输入  : 	- x: 显示位置横向坐标	 
         	- y: 显示位置纵向坐标 
 			- str: 显示的英文字符串
 			- Color: 字符颜色   
 			- bColor: 背景颜色		
------------------------------------------------------*/
void LCD_Write_String(uint16 x,uint16 y,const uint8 *p,uint16 Color,uint16 bColor)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX)
		{
			x = 0;
			y += 12;
		}
        if(y>MAX_CHAR_POSY)
		{
			y=x=0;
			LCD_Clear_All(Black);
		}
        LCD_Write_Char(x,y,*p,Color,bColor);
        x += 8;
        p++;
    }  
}
#endif
/*---------------------------------------------
 描述：显示单个汉字字符
 输入: (x,y)汉字显示坐标    str: 中文字符串首址
        Color: 字符颜色   	bkColor: 背景颜色     
 举例：LCD_Char_CH(200,100,"好",0,0);
 注意：如果输入大于1的汉字字符串，显示将会截断
       只显示最前面一个汉字
---------------------------------------------*/    
void LCD_Write_Char_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor)
{
    uint8 i,j;
    uint8 buffer[32];
    uint16 tmp_char = 0;
	uint32 pos;

#ifdef LARGE_CHN_LIB	 //使用大字库的时候编译此段
    pos = Get_GBKChineseCode(str);  /* 计算出该字在GBK_Chinese中的起始位置 */
    for(i=0; i<32; i++)
	{
		buffer[i] = GBK_Large[pos];//从pos开始往后取出31位数据存入pBuffer中
		pos++;
	} 
#endif 

#ifdef SMALL_CHN_LIB   //使用小字库的时候编译此段
	pos = Get_GBKSmallCode(str);
	for(i=0; i<32; i++)
	{	
		//从ArrayCode[0]开始往后取出31位数据存入buffer中
		buffer[i] = GBKSmall[pos].ArrayCode[i];
	} 
#endif
	   
	for (i=0;i<16;i++)	 //把字体逐点打印出来
    {
        tmp_char = buffer[i*2];
        tmp_char = (tmp_char<<8);
        tmp_char |= buffer[2*i+1];
        for (j=0;j<16;j++)
        {
            if ( (tmp_char >> 15-j) & 0x01 == 0x01)
            {
                Draw_Point(x+j,y+i,Color);
            }
            else
            {
                Draw_Point(x+j,y+i,bColor);
            }
        }
    }
}
/*------------------------------------------------------
 描述  ：在指定坐标处显示16*16大小的指定颜色汉字字符串
 输入  : 	- x: 显示位置横向坐标	 
         	- y: 显示位置纵向坐标 
 			- str: 显示的中文字符串
 			- Color: 字符颜色   
 			- bColor: 背景颜色		
------------------------------------------------------*/    
void LCD_Write_String_CH(uint16 x,uint16 y,const uint8 *str,uint16 Color,uint16 bColor)  
{
    while(*str != 0)
    {
	    LCD_Write_Char_CH(x,y,str,Color,bColor);      
        str += 2 ;
        x += 16 ;	
    }
}
/*-------------------------------------------------------
 函数功能: 获取汉字在GBK_Chinese中的起始位置
 函数参数: 字符指针c
 返 回 值: uint型数据
 调用示例: POS = Get_GBKChineseCode(str)
--------------------------------------------------------*/
#ifdef LARGE_CHN_LIB   //如果使用大字库则编译此段
uint32 Get_GBKChineseCode(const unsigned char *c)
{ 
    unsigned char High8bit,Low8bit;
    unsigned int pos;
    High8bit = *c;     /* 取高8位数据 */
    Low8bit  = *(c+1);  /* 取低8位数据 */
    
    pos = ((High8bit - 0xB0)*94 + Low8bit - 0xA1)*2*16;  //计算出内码	
    return pos;  
}
#endif
/*-------------------------------------------------------
 函数功能: 获取汉字在GBK_Small中的起始位置
 函数参数: 字符指针c
 返 回 值: uint型数据
 调用示例: POS = Get_GBKSmallCode(str)
--------------------------------------------------------*/ 
#ifdef SMALL_CHN_LIB  //如果使用小字库则编译此段
uint32 Get_GBKSmallCode(const uint8 chn[2])
{
	unsigned int i;
	for(i=0; i<WORD_NUMBER; i++)	//WORD_NUMBER为小字库的数量,定义在GBK_Small.h中
	{
		if((GBKSmall[i].InnerCode[0]==chn[0]) && (GBKSmall[i].InnerCode[1]==chn[1]))
			return i;  //返回该字的位置
	}
	return 0;
}
#endif
/*-----------------------------------------------------------------
 功    能：在指定座标范围显示一副BMP图片
 入口参数：StartX行起始座标,StartY列起始座标
 说    明：图片取模格式为水平扫描，16位颜色模式  取模软件img2LCD
 调用示例：Draw_Picture(0,0,0,(u16*)demo);
------------------------------------------------------------------*/
void LCD_Write_Bmp(uint16 x,uint16 y,uint16 lenth,uint16 wide,const uint8 *p)
{      
    uint32 size,temp; 
    //设定一个图片所占的窗口大小 
	
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//起始地址X
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(((uint16)x+lenth-1)>>8);//结束地址X
	LCD_WR_Data(((uint16)x+lenth-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//起始地址Y
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+wide-1)>>8);	    	//结束地址Y
	LCD_WR_Data((y+wide-1)&0x00ff);
	LCD_WR_REG(0x2c);	 
	temp=(uint32)lenth*wide*2;
	for(size=0;size<temp;size++)
		LCD_WR_Data_8(p[size]); 
}  
/*-----------------------------------------------------------------
 功    能：在指定座标范围显示一副图片
 入口参数：StartX行起始座标,StartY列起始座标
 说    明：图片取模格式为水平扫描，16位颜色模式  取模软件img2LCD
 调用示例：Draw_Picture(0,0,0,(u16*)demo);
------------------------------------------------------------------*/
void Draw_Picture(uint16 x,uint16 y,uint8 *pic)
{
	unsigned int  i=8, len;	//从图像数组的第8+1位开始递增
	uint16 temp,length,wide;
	length =((uint16)(pic[2]<<8)+pic[3]);	  	//从图像数组里取出图像的长度
	wide   =((uint16)(pic[4]<<8)+pic[5]);	  	//从图像数组里取出图像的高度
	LCD_WR_REG(0x002A);				    
	LCD_WR_Data(x>>8);	    			//起始地址X
	LCD_WR_Data(x&0x00ff);
	LCD_WR_Data(((uint16)x+length-1)>>8);//结束地址X
	LCD_WR_Data(((uint16)x+length-1)&0x00ff);
    LCD_WR_REG(0x002b);	
	LCD_WR_Data(y>>8);	    			//起始地址Y
	LCD_WR_Data(y&0x00ff);
	LCD_WR_Data((y+wide-1)>>8);	    	//结束地址Y
	LCD_WR_Data((y+wide-1)&0x00ff);
	LCD_WR_REG(0x2c);		
	len=2*((uint16)(pic[2]<<8)+pic[3])*((uint16)(pic[4]<<8)+pic[5]);   //计算出图像所占的字节数  
	while(i<(len+8)) 
	{	
		temp=(uint16)( pic[i]<<8)+pic[i+1];	//16位总线,需要一次发送2个字节的数据
		LCD_WR_Data(temp);							//将取出的16位像素数据送入显示区
		i=i+2;										    //取模位置加2，以为获取下一个像素数据
	}
}       
