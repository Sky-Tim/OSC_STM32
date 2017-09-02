/*---------------------------------------------------------
	      	   底层硬件接口配置程序
	
	说明: 配置示波器的外设包括继电器、CD4051多路模拟开关、
		  独立按键管脚、发光二极管、蜂鸣器的开关管脚.

    时间: 2014年1月22日 
---------------------------------------------------------*/
#include "pincfg.h"
#include "ucos_ii.h"
/*---------------------------------------------------
	管脚配置
---------------------------------------------------*/
void PinCfg(void)
{
  PinCfg_SWITCH();
  PinCfg_JDQ();
  PinCfg_CD4051();
  PinCfg_KEY();
}
/*---------------------------------------------------
	继电器配置引脚
	PG5->RL1
	PG3->RL2
---------------------------------------------------*/
void PinCfg_JDQ(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	
	IO_Init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_3;				    
	IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOG, &IO_Init);	  
}
/*---------------------------------------------------
	CD4051配置引脚
	PB12->A
	PB14->B
	PD12->C
---------------------------------------------------*/
void PinCfg_CD4051(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);	
	IO_Init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;				    
	IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &IO_Init);
	
	IO_Init.GPIO_Pin = GPIO_Pin_12;
	IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOD, &IO_Init);
}
/*---------------------------------------------------
	LED配置引脚
	PE0->BOARD_LED1
	PE2->BOARD_LED2
	PE4->DAC_LED
	PE5->BEEP
---------------------------------------------------*/
void PinCfg_SWITCH(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
	IO_Init.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5;				    
	IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOE, &IO_Init);	  
}
/*---------------------------------------------------
	按键配置引脚
	PB10->KEY1
	PB11->KEY2
---------------------------------------------------*/
void PinCfg_KEY(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	IO_Init.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;				    
	IO_Init.GPIO_Mode = GPIO_Mode_IPU;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &IO_Init);
}
/*---------------------------------------------------
	蜂鸣器鸣响times次
---------------------------------------------------*/
void PinCfg_Beep(unsigned char times)
{
	char i;
	for(i=0;i<times;i++)
	{
	 	BEEP = 1;
		OSTimeDlyHMSM(0,0,0,100);
		BEEP = 0;
		OSTimeDlyHMSM(0,0,0,100);
	}
}