/*---------------------------------------------------------------------------------
	    				STM32 4.3TFT彩屏底层驱动程序
 
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
#include "tft_drive.h"
#include "stm32f10x.h"
#include "delay.h"

/*---------------------------------------------------------
		与彩屏有关的参数,具体作用现在还不清楚
--------------------------------------------------------*/
unsigned int  HDP=479; //水平分辨率480
unsigned int  VDP=271; //垂分辨率272
unsigned int  HT=531;  //水平总周期532
unsigned int  HPS=43;
unsigned int  LPS=8;
unsigned char HPW=1;
unsigned int  VT=288;
unsigned int  VPS=12;
unsigned int  FPS=4;    
unsigned char VPW=10;
 

void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}			 

void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}

uint16_t LCD_RD_data(void)
{
	uint16_t a=0;
	
	a = *(__IO uint16_t *) (Bank1_LCD_D);   //空操作必须的不能删除
	a = *(__IO uint16_t *) (Bank1_LCD_D);   //读出的实际16位像素数据	  
	
	return a;	
}

void LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}

void LCD_WR_Data_8(unsigned int val)
{
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}
/*---------------------------------------------------------
	函数功能: 对SSD1963芯片控制器初始化参数
	函数参数: 无
--------------------------------------------------------*/
void LCD1963_Init(void)
{	
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    Software_Delay(0xAFFFF);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
	Software_Delay(0xAFFFF);

    LCD_WR_REG(0x00E2);	        //PLL 倍频到120M   PLL=10*36/3=120M
	LCD_WR_Data(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WR_Data(0x0002);
	LCD_WR_Data(0x0004);
	
	LCD_WR_REG(0x00E0);         
	LCD_WR_Data(0x0001);
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x00E0);
	LCD_WR_Data(0x0003);		// PLL 使能  PLL作为时钟
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x0001);         // 软件复位
	Software_Delay(0xAFFF);
	LCD_WR_REG(0x00E6);	        //PLL setting for PCLK, depends on resolution
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x0033);
	LCD_WR_Data(0x0032);

    LCD_WR_REG(0x00B0);	        //设置LCD模式
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);
	LCD_WR_Data((HDP>>8)&0X00FF);  //Set HDP
	LCD_WR_Data(HDP&0X00FF);
    LCD_WR_Data((VDP>>8)&0X00FF);  //Set VDP
	LCD_WR_Data(VDP&0X00FF);
    LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B4);	//HSYNC
	LCD_WR_Data((HT>>8)&0X00FF);  //Set HT
	LCD_WR_Data(HT&0X00FF);
	LCD_WR_Data((HPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(HPS&0X00FF);
	LCD_WR_Data(HPW);			   //Set HPW
	LCD_WR_Data((LPS>>8)&0X00FF);  //Set HPS
	LCD_WR_Data(LPS&0X00FF);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00B6);	//VSYNC
	LCD_WR_Data((VT>>8)&0X00FF);   //Set VT
	LCD_WR_Data(VT&0X00FF);
	LCD_WR_Data((VPS>>8)&0X00FF);  //Set VPS
	LCD_WR_Data(VPS&0X00FF);
	LCD_WR_Data(VPW);			   //Set VPW
	LCD_WR_Data((FPS>>8)&0X00FF);  //Set FPS
	LCD_WR_Data(FPS&0X00FF);

	LCD_WR_REG(0x00BA);
	LCD_WR_Data(0x000F);    //GPIO[3:0] out 1

	LCD_WR_REG(0x00B8);
	LCD_WR_Data(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WR_Data(0x0001);    //GPIO0 normal

	LCD_WR_REG(0x0036);            //rotation
	LCD_WR_Data(0x0000);


	LCD_WR_REG(0x00F0);             //16位  565模式
	LCD_WR_Data(0x0003);


	Software_Delay(0xAFFF);

	LCD_Clear_All(Black);
	LCD_WR_REG(0x0029); //display on

	LCD_WR_REG(0x00BE); //set PWM for B/L
	LCD_WR_Data(0x0006);
	LCD_WR_Data(0x0080);
	
	LCD_WR_Data(0x0001);
	LCD_WR_Data(0x00f0);
	LCD_WR_Data(0x0000);
	LCD_WR_Data(0x0000);

	LCD_WR_REG(0x00D0);//设置动态背光控制配置 
	LCD_WR_Data(0x000D);
}
/*---------------------------------------------------------
	函数功能: 对STM32的FSMC总线进行初始化
	函数参数: 无
--------------------------------------------------------*/
void FSMC_LCD_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  FSMC_NORSRAMTimingInitStructure;	
    GPIO_InitTypeDef GPIO_InitStructure;
	//使能IO口,FSMC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE , ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC , ENABLE);
	//PD13->LCD背光控制
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	//PE1->REST复位
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	//复用端口为FSMC接口 FSMC-D0--D15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	  //复用输出
    GPIO_Init(GPIOD, &GPIO_InitStructure);   
   	//复用端口为FSMC接口 FSMC-D0--D15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure);    
    //FSMC NE1  LCD->CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //FSMC LCD->RS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
    GPIO_Init(GPIOD, &GPIO_InitStructure); 	
    GPIO_SetBits(GPIOD, GPIO_Pin_13);  //LCD开背光
	//FSMC时序配置,具体参数为何是这样还未研究
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 0x02;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 0x05;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	/* NOR FLASH的BANK 1*/
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	/* 数据线和地址线不复用 */
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
	/* FSMC内存类型NOR */
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	/* FSMC内存数据宽度16位 */
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	/* 异步写模式,禁止突发模式 */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	/* 该参数只在突发模式下有效,等待信号极性为低 */
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	/* 禁止非对齐突发模式 */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	/* 该参数只在突发模式下有效,在等待状态之前等待信号激活 */
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	/* FSMC写使能 */
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	/* FSMC等待信号关闭 */
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	/* FSMC扩展模式关闭 */
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	/* 禁止写突发 */
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	//FSMC读写时序配置
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
 	//FSMC写时序配置
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 		
    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
