/*------------------------------------------------------------------------------------
        		   	  STM32+UCOS+UCGUI示波器
	   
	   					    任务列表
	   +---------------------+-------------+-----------+
	   |      任务名称       | 任务优先级  |  任务堆栈 |
	   +---------------------+-------------+-----------+	   
	   |   TASK_MAIN         |     11      |   2048    |
	   +---------------------+-------------+-----------+
	   |   TASK_RTC   	     |     12      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_SD	         |     13      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_TOUCHSCREEN	 |     14      |    512    |
	   +---------------------+-------------+-----------+
	   |   TASK_GUI	 		 |     15      |   1024    |
	   +---------------------+-------------+-----------+
	   |   TASK_START	     |     5       |    64     |
	   +---------------------+-------------+-----------+
	   

 时间: 2013年11月13日       BoX编写				
-------------------------------------------------------------------------------------*/  
#include "ucos_ii.h"   
#include "stdio.h"
#include "app.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "oscilloscope.h"
#include "indkey.h"
#include "timer.h"
#include "EXTI.H"
#include "adc.h"
#include "iwdg.h"
#include "tsc2046.h"

#include "task_main.h"
#include "task_gui.h"
#include "task_rtc.h"
#include "task_sd.h"
#include "task_touchscreen.h"

#include "GUI.h"
/*-----------------------------------------
				声明任务栈
 UCOSII的任务堆栈没有8字节对齐,在声明任务堆
 栈时,强制8字节对齐就可以了,系统默认是4字节
 对齐.否则sprintf时会出问题,系统会崩溃.
------------------------------------------*/
__align(8) OS_STK Task_TouchScreen_Stk[TASK_TOUCHSCREEN_STK_SIZE];
__align(8) OS_STK Task_Main_Stk[TASK_MAIN_STK_SIZE];
__align(8) OS_STK Task_RTC_Stk[TASK_RTC_STK_SIZE];
__align(8) OS_STK Task_SD_Stk [TASK_SD_STK_SIZE];
__align(8) OS_STK Task_GUI_Stk[TASK_GUI_STK_SIZE];
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern u16  ADC1_DMA_Value;
extern u8   LCD_Buffer[LCD_BUFFER_SIZE];
extern u16  Tpx,Tpy,ZBX,ZBY;		  //触摸屏AD值,坐标值
extern void BSP_Init(void);

extern  WaveType    WaveInfo;			  //波形参数
extern  WaveMode    WaveCtrl;			  //控制参数
extern  FG_WaveType FG_WaveInfo;	      //信号发生器参数
/*-----------------------------------------
		    	开始任务
------------------------------------------*/
void Task_Start(void *pdata)
{
 	 pdata = pdata;
	 BSP_Init();		//完成片上外设的初始化
	 OSStatInit();		//初始化统计任务
	 
	 while(1)
	 {	 
//	 	 ShowWelcomeScreen();
//		 OSTimeDlyHMSM(0,0,3,0);
	 	 /*触摸屏任务*/
		 
	  	 OSTaskCreateExt(Task_TouchScreen,
                    	(void *)0,
                    	&Task_TouchScreen_Stk[TASK_TOUCHSCREEN_STK_SIZE - 1],
                    	TASK_TOUCHSCREEN_PRIO,
                    	TASK_TOUCHSCREEN_PRIO,
                    	&Task_TouchScreen_Stk[0],
                    	TASK_TOUCHSCREEN_STK_SIZE,
                    	(void *)0,
                    	OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		
        /*实时时钟任务*/
        OSTaskCreateExt(Task_RTC,
	                    (void *)0,
	                    &Task_RTC_Stk[TASK_RTC_STK_SIZE - 1],
	                    TASK_RTC_PRIO,
	                    TASK_RTC_PRIO,
	                    &Task_RTC_Stk[0],
	                    TASK_RTC_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
        /*SD卡任务*/
        OSTaskCreateExt(Task_SD,
	                    (void *)0,
	                    &Task_SD_Stk[TASK_SD_STK_SIZE - 1],
	                    TASK_SD_PRIO,
	                    TASK_SD_PRIO,
	                    &Task_SD_Stk[0],
	                    TASK_SD_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		/*GUI任务*/
		OSTaskCreateExt(Task_GUI,
                    	(void *)0,
	                    &Task_GUI_Stk[TASK_GUI_STK_SIZE - 1],
	                    TASK_GUI_PRIO,
	                    TASK_GUI_PRIO,
	                    &Task_GUI_Stk[0],
	                    TASK_GUI_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

		/*主任务*/
		OSTaskCreateExt(Task_Main,
	                    (void *)0,
	                    &Task_Main_Stk[TASK_MAIN_STK_SIZE - 1],
	                    TASK_MAIN_PRIO,
	                    TASK_MAIN_PRIO,
	                    &Task_Main_Stk[0],
	                    TASK_MAIN_STK_SIZE,
	                    (void *)0,
	                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
  	    
//		PinCfg_Beep(1); 			   //蜂鸣器响起提示系统启动成功
        OSTaskSuspend(OS_PRIO_SELF);   //挂起Task_Start任务		
	 }
}
/*-----------------------------------------
		    	触摸屏任务
------------------------------------------*/	 
void Task_TouchScreen(void *pdata)
{
	pdata = pdata;
	while(1)
	{	
		TP_Read(&Tpx,&Tpy);
		TP_ADtoZB(&Tpx,&Tpy,&ZBX,&ZBY);	 //计算触摸坐标
		TouchEventDetected();			 //检测触摸事件
		BOARD_LED1 = !BOARD_LED1;
		OSTimeDlyHMSM(0,0,0,100);
	}
}
/*-----------------------------------------
		    	Real Time Clock任务
------------------------------------------*/
void Task_RTC(void *pdata)
{
	pdata = pdata;	
	while(1)
	{	
		u8 AlarmTemp;
		GetFrequence();		   //获取时间参数并显示
		AlarmTemp = GetTempSensor();	
		
		if(AlarmTemp>60)	   //芯片保护温度报警定值60℃
			BEEP = 1;
		else if(AlarmTemp>50)
			PinCfg_Beep(3);	   //接近红线短鸣3声
		else
			BEEP = 0;
	 	OSTimeDlyHMSM(0,0,1,500);
	} 	
}
/*-----------------------------------------
		     	主任务 
------------------------------------------*/
void Task_Main(void *pdata)
{	
	pdata = pdata;					
	WaveCtrl.TimeBase = 99;			//上电默认时基99
	WaveCtrl.Gain = 3;				//上电默认增益号3
	while(1)
	{
//		TaskStackChack();			//是否堆栈使用情况检查
		GetWaveADCValue();			//核心函数
		IWDG_Feed();       			//1000ms内喂狗
		BOARD_LED2 = !BOARD_LED2;
		OSTimeDlyHMSM(0,0,0,50);
	}	
}
/*-----------------------------------------
		    	SD任务 
------------------------------------------*/
void Task_SD(void *pdata)
{
	pdata = pdata;
	while(1)
	{
		SendDataToPC();				//发送编码数据到上位机
	 	OSTimeDlyHMSM(0,0,0,999);
	}
}
/*-----------------------------------------
		    	GUI任务 
------------------------------------------*/ 

void Task_GUI(void *pdata)
{
	pdata = pdata;
	DrawControlPanel();
	while(1)
	{	
		DisplayWaveInfo();		  	//显示参数	
		OSTimeDlyHMSM(0,0,0,500);
	}
}
