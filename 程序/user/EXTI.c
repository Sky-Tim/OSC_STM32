/*-------------------------------------------------------------------------
       外部IO口中断配置程序
 说明: EXTI_Config函数配置IO口模式,具体的一些注意事项已经在注释中说明。
	   NVIC_Config函数配置中断向量表和优先级等,注意事项已经在注释说明。
 提醒: 中断服务程序写在stm32f10x_it.c中
	   中断服务函数名不能乱写,只能按照是哪个中断线就写哪个规定的中断函数名 
       具体的中断函数名请到startup_stm32f10x_hd.s文件中62行寻找相应的名字。
	   中断名在stm32f10x.h文件中188行可以找到各种中断名列表,根据需要选择
 时间: 2013年7月22日 BoX编写 
--------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "EXTI.H"
#include "pincfg.h"
#include "ucos_ii.h"
#include "misc.h"
#include "task_main.h"
/*---------------------------------
			变量声明
----------------------------------*/
uint8_t InterruptTimes = 0;		 //中断进入次数
EXTI_InitTypeDef EXTI_IO_Init;	 //需要在中断改变触发沿,只能使用全局变量
extern WaveMode WaveCtrl;
extern WaveType WaveInfo;
/*---------------------------------------------------------------
	函数功能: 外部中断配置模块,配置A0,A1口为外部上升沿中断 
----------------------------------------------------------------*/
void EXTI_Config(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//配置PA0,PA1为脉冲输入口	
  	IO_Init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;				    
  	IO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;		
  	GPIO_Init(GPIOA, &IO_Init);
	NVIC_Config(); 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//中断模式
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;    //上升沿触发中断
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //使能中断
	EXTI_Init(&EXTI_IO_Init);	 					    //写入配置
    
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 
	EXTI_IO_Init.EXTI_Line = EXTI_Line1;
	EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		//中断模式
	EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;    //上升沿触发中断
	EXTI_IO_Init.EXTI_LineCmd = ENABLE;				    //使能中断
	EXTI_Init(&EXTI_IO_Init);	 					    //写入配置
}
/*---------------------------------------
	函数功能: 嵌套向量中断控制器配置模块 
---------------------------------------*/
static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVICInit;
	NVICInit.NVIC_IRQChannel = EXTI0_IRQn;			 //0-4独立IV,5-9共用EXTI9_5_IRQn IV,10-15共用EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2;  //抢占优先级2
    NVICInit.NVIC_IRQChannelSubPriority = 0;  		 //响应优先级0
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //使能中断
	NVIC_Init(&NVICInit);                            //写入配置
	
	NVICInit.NVIC_IRQChannel = EXTI1_IRQn;			 //0-4独立IV,5-9共用EXTI9_5_IRQn IV,10-15共用EXTI15_10_IRQn IV	
	NVICInit.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级1
    NVICInit.NVIC_IRQChannelSubPriority = 0;  		 //响应优先级0
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	         //使能中断
	NVIC_Init(&NVICInit);                            //写入配置 							 //写入配置
}
/*---------------------------------------
 函数功能: PA0外部中断服务程序
 函数实现: 通过测量两次上升沿完成一个周期
           的计时,第一个上升沿打开定时器
		   第二个上升沿关闭定时器,读出定
		   时器的数,清空定时器完成一次测量 
---------------------------------------*/
void EXTI0_IRQHandler(void)
{
	OSIntNesting++;
	InterruptTimes++;
	
	if(InterruptTimes == 1)			//第1次进入中断后打开定时器5且变成下降沿触发
	{	
		TIM_Cmd(TIM5,ENABLE);
		EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
		EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		
		EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Falling;    
		EXTI_IO_Init.EXTI_LineCmd = ENABLE;				  
		EXTI_Init(&EXTI_IO_Init);
	}

	if(InterruptTimes == 2)			//第2次进入中断后获取5CNT且变成上升沿触发
	{ 	
		WaveInfo.LowWidth = TIM5->CNT;
		EXTI_IO_Init.EXTI_Line = EXTI_Line0; 
		EXTI_IO_Init.EXTI_Mode = EXTI_Mode_Interrupt;  		
		EXTI_IO_Init.EXTI_Trigger = EXTI_Trigger_Rising;   
		EXTI_IO_Init.EXTI_LineCmd = ENABLE;				   
		EXTI_Init(&EXTI_IO_Init);
	}
						 
	if(InterruptTimes == 3)			//第3次进入中断后关闭定时器5且关闭外部中断0
	{
	 	TIM_Cmd(TIM5,DISABLE);
		EXTI->IMR &= ~EXTI_Line0; 	
	}
	 
	EXTI_ClearFlag(EXTI_Line0);		
	OSIntExit();
}
/*---------------------------------------
 函数功能: PA1外部中断服务程序
 函数实现: 通过一次上升沿或一次下降沿完成
           一次一系列的AD转换的触发，如果
		   不采用触发装置,则采集到的波形
		   会晃动严重甚至无法观察,采用边沿
		   触发之后可以稳定观测波形。 
---------------------------------------*/
void EXTI1_IRQHandler(void)
{
	OSIntNesting++;		
	if(WaveCtrl.TriggerMode == Trigger_Rising)	   //上升沿触发AD
	{
	 	TIM_Cmd(TIM3,ENABLE);
		EXTI->RTSR |= EXTI_Line1;	   
    	EXTI->FTSR &= ~EXTI_Line1;
	}

	if(WaveCtrl.TriggerMode == Trigger_Falling)	   //下降沿触发AD
	{
	 	TIM_Cmd(TIM3,ENABLE);
		EXTI->RTSR &= ~EXTI_Line1;	   
    	EXTI->FTSR |=  EXTI_Line1;	
	}

	EXTI->IMR &= ~EXTI_Line1;					   //完成1次AD触发后关闭外部中断1,下次何时触发由任务决定
	EXTI_ClearFlag(EXTI_Line1);		
	OSIntExit();
}
					   
