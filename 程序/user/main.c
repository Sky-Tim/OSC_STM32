/*------------------------------------------------------------------------------------
        		   					STM32示波器
 硬件平台:
 			主控器: STM32F103ZET6 64K RAM 512K ROM
			屏幕器: SSD1963 
			分辨率: 480x272 16位色
           	触摸屏: TSC2046
			模拟电路: OP  - TL084
					  OP  - u741
					  SW  - CD4051
					  CMP - LM311
					  PWR - LM7805
					      - LM7905
						  - MC34063
						  - AMS1117-3.3
					  DRI - ULN2003
			继电器：信号继电器
		    电源:   DC +12V

 软件平台:
 			开发环境: RealView MDK-ARM uVision4.10
			C编译器 : ARMCC
			ASM编译器:ARMASM
			连接器:   ARMLINK
			实时内核: uC/OS-II 2.90实时操作系统
			GUI内核 : uC/GUI   3.90图形用户接口
			底层驱动: 各个外设驱动程序
	
	ROM Size = Code + RO-data +RW-data
	RAM Size = RW-data + ZI-data
	Program Size: Code=56024 RO-data=8272 RW-data=256 ZI-data=29912          
 
 时间: 2013年11月9日       BoX编写于大二上学期
 
 版本: V1.0 - 2013/11/9
       V1.1 - 2014/2/8
	   V3.0 - 2014/2/19				
-------------------------------------------------------------------------------------*/   
#include "stm32f10x.h"
#include "ucos_ii.h"
#include "app.h"
#include "GUI.h"

#include "usart1.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "dac.h"
#include "adc.h"
#include "iwdg.h"
#include "timer.h"
#include "EXTI.H"
#include "oscilloscope.h"
#include "indkey.h"
#include "tsc2046.h"

#include "task_rtc.h"
#include "task_gui.h"
#include "task_sd.h"


/*-----------------------------------------
				声明起始任务栈
------------------------------------------*/
OS_STK  Task_Start_Stk[TASK_START_STK_SIZE]; 

/*-----------------------------------------
 因为涉及到对共享资源的访问,创建互斥信号量
------------------------------------------*/
OS_EVENT *LCD_Buffer_MUTEX;
OS_EVENT *USART_Buffer_MUTEX;
OS_EVENT *SDtoRAM_Buffer_MUTEX;
/*-----------------------------------------
				主 函 数
------------------------------------------*/    
int main(void)    
{    
	 INT8U err;
     SystemInit();		 //初始化RCC时钟
	 OSInit(); 
	  		 
	 LCD_Buffer_MUTEX     = OSMutexCreate(4,&err);	//创建3个共享资源互斥信号量
	 USART_Buffer_MUTEX   = OSMutexCreate(4,&err);
	 SDtoRAM_Buffer_MUTEX = OSMutexCreate(4,&err);
	    
     OSTaskCreate(Task_Start,(void *)0,&Task_Start_Stk[TASK_START_STK_SIZE-1],TASK_START_PRIO); //起始任务   
	 
	 OSStart();       
}
/*-------------------------------------------------------------------------------
 函数功能:初始化各种外设
 说    明:因为跑操作系统,所以外设的初始化应该放在操作系统的初始任务中完成,不能
          在while(1)循环外部完成外设的初始化工作,否则操作系统可能无法启动.
		  本函数在app.c中被调用
-------------------------------------------------------------------------------*/
void BSP_Init(void)
{
	OS_CPU_SR  cpu_sr = 0u;
	OS_ENTER_CRITICAL();
	DelayInit();		 //初始化延时
	PinCfg();			 //外部器件控制配置
	FSMC_LCD_Init();	 //FSMC总线配置		  
	GUI_Init();			 //初始化UCGUI界面
	TSC2046_Config();	 //初始化触摸控制器
	USART1_Config();	 //初始化串口
	DAC_Config();		 //初始化DAC1
	ADC1_Init();		 //初始化ADC1
	EXTI_Config();		 //初始化外部中断
	Key_EXTI_Config();	 //初始化按键中断
	TIM5_Config(1999,71);  //TIM5以1MHz频率计数,每2ms溢出中断
//	TIM4_Config(59999,71); //TIM4以1MHz频率计数,每60ms溢出中断
	RTC_Init();	 	 	  //初始化RTC
//	SD_Init();
	JDQ_ACDC = 1;		  //交流耦合
	ManualGainScan(3);    //调试用
	IWDG_Init(4,625);     //喂狗时间为1000ms
	OS_EXIT_CRITICAL();	 
}
