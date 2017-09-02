/*------------------------------------------------------------------------
	STM32通用定时器2,3,4,5,8配置程序
	
	说明: 1) 定时器时钟频率(Hz)=72MHZ/(时钟预分频+1)
		     即CK_CNT=72000000/(TIM_Prescaler+1)
		     发生中断时间(s)=(TIM_Prescaler+1)*(TIM_Period+1)/CK_INT
		     CK_INT默认为72000000Hz 
		     见参考手册263页

		  2) 定时器使用情况一览
		  	 TIM1 - 未使用
		  	 TIM2 - TRGO事件触发DAC1转换
			 TIM3 - TRGO事件触发ADC1转换
			 TIM4 - 未使用
			 TIM5 - 运行频率1MHz,测量脉冲宽度频率
			 TIM6 - 未使用
			 TIM7 - 未使用
			 TIM8 - 未使用

	时间: 2013年7月26日 BoX编写
-----------------------------------------------------------------------*/
#include "timer.h"
#include "stm32f10x.h"
#include "pincfg.h"
#include "ucos_ii.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern u32  IntFullTime; //测量矩形波TIM5中断溢出次数
/*-----------------------------------------------
	函数功能: TIM5中断溢出时间设置
	函数参数: ARR/10寄存器值0-6553ms
-----------------------------------------------*/
void TIM5_Set_Time(unsigned short int Auto_Reload)
{
	TIM5_Config((Auto_Reload*10)-1,72);  //72为预分频系数,可自由设定
	TIM_Cmd(TIM5,ENABLE);    			 //使能TIM5
}
/*-----------------------------------------------
	函数功能: TIM5定时器为测量周期提供计时
	函数参数: ARR寄存器值0-65535,预分频值0-65535
    参 考 值: TIM5_Config(1999,71)
	          计数频率1MHz,中断频率500Hz
			  计数器每1us加1,中断每2ms产生一次		  			  
-----------------------------------------------*/
void TIM5_Config(unsigned short int Period,unsigned short int Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	
	//配置TIM5
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 			//时钟预分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_Period = Period;			        //自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //时钟分频1
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);  					
	//配置TIM5中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  	    //响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	            
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM5,ENABLE); 	
}
/*-----------------------------------------------
	函数功能: TIM4定时器为测量占空比提供计时
	函数参数: ARR寄存器值0-65535,预分频值0-65535
    参 考 值: TIM5_Config(59999,71)
	          计数频率1MHz,中断频率16.6Hz
			  计数器每1us加1,中断每60ms产生一次		  			  
-----------------------------------------------*/
void TIM4_Config(unsigned short int Period,unsigned short int Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	//配置TIM5
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler; 			//时钟预分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_Period = Period;			        //自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //时钟分频1
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

	TIM_Cmd(TIM4,ENABLE); 	
}
/*-----------------------------------------------
 函数功能:TIM5中断服务程序
 函数说明:在中断中记录TIM5计数器的溢出次数
          在oscilloscope.c中完成中断溢出次数的清零
-----------------------------------------------*/
void TIM5_IRQHandler(void)
{
	OSIntNesting++;							    //进入中断通知UCOS
	IntFullTime++;								//溢出次数加1  		                      
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断
	OSIntExit(); 
}
	