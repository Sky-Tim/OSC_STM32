/*-----------------------------------------------
		独立按键端口配置及检测程序
	说明:	已经将端口配置和按键扫描程序封装成型
	        根据程序实际需要更改相应的参数即可。
	时间:	2013年7月22日
------------------------------------------------*/
#include "indkey.h"
#include "stm32f10x.h"
#include "delay.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;
/*-----------------------------------------------
	函数功能:	独立按键检测
	函数参数:	端口组名GPIOx,引脚名GPIO_Pin
	函数回值:	INT8U类型 按键值0,1
------------------------------------------------*/
unsigned char Key_Scan(GPIO_TypeDef* GPIOx,unsigned short int GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED)  //按下接通低电平
	{
		delayms(3);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED)
		{
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_PRESSED);//等待按键释放
			return KEY_PRESSED;
		}
		else
			return KEY_UNPRESS;
	}
	else
		return KEY_UNPRESS;
}
/*---------------------------------------------------------------
	函数功能: 外部中断配置模块,配置B10,B11口为外部下降沿中断 
----------------------------------------------------------------*/
void Key_EXTI_Config(void)
{
	NVIC_InitTypeDef NVICInit;
	EXTI_InitTypeDef EXTI_IO_Init;

	NVICInit.NVIC_IRQChannel = EXTI15_10_IRQn;			 //0-4独立IV,5-9共用EXTI9_5_IRQn IV,10-15共用EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级2
    NVICInit.NVIC_IRQChannelSubPriority = 1;  		 //响应优先级1
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //使能中断
	NVIC_Init(&NVICInit);                            //写入配置 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	EXTI_IO_Init.EXTI_Line = EXTI_Line10; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//中断模式
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发中断
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //使能中断
	EXTI_Init(&EXTI_IO_Init);	 					    //写入配置

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
	EXTI_IO_Init.EXTI_Line = EXTI_Line11; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//中断模式
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发中断
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //使能中断
	EXTI_Init(&EXTI_IO_Init);	 					    //写入配置
}
/*---------------------------------------------------------------
	函数功能: 独立按键中断 
----------------------------------------------------------------*/
void EXTI15_10_IRQHandler(void)
{
	OSIntNesting++;
	if(EXTI_GetITStatus(EXTI_Line10) == SET)
	{	   
	   ManualGainScan(++WaveCtrl.Gain);
	   if(WaveCtrl.Gain == 9)
	   	WaveCtrl.Gain = 1;
	   EXTI_ClearFlag(EXTI_Line10);
	}	
	
	if(EXTI_GetITStatus(EXTI_Line11) == SET)
	{	   
	   ManualGainScan(--WaveCtrl.Gain);
	   if(WaveCtrl.Gain == 0)
	   	WaveCtrl.Gain = 8;
	   EXTI_ClearFlag(EXTI_Line11);
	}		
	OSIntExit();
}
