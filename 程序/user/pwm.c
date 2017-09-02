/*---------------------------------------
			PWM配置程序
 说明: 本程序配置通过把A7的PWM功能重映射
 	   到PB5端口来实现PWM控制LED产生呼吸
	   作用,配置过程具有参考作用,使用价
	   值大,并且我重新封装了新的函数,使
	   得PWM的配置和使用更加便捷直观。
 时间: 2013年7月26日 BoX编写
----------------------------------------*/
#include "pwm.h"
#include "stm32f10x.h"
/*---------------------------------------
 函数功能: 定时器3通道2配置PWM定时器
 函数参数: 自动重装值Auto_Reload 0-65535
 		   预分频 Clock_Div 0-65535
----------------------------------------*/
void PWM_TIM2_CH2_Config(uint16_t Auto_Reload,uint16_t Clock_Div)
{	
	GPIO_InitTypeDef IO_Init;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	 //使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //使能AFIO时钟
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD , ENABLE);	
 	
	IO_Init.GPIO_Pin = GPIO_Pin_5;				    
  	IO_Init.GPIO_Mode = GPIO_Mode_AF_PP;				 //PB5复用推挽输出
  	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;	
  	GPIO_Init(GPIOB, &IO_Init);

	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);	 //TIM3部分重映射 TIM3_CH2->PB5

	TIM_TimeBaseStructure.TIM_Prescaler =  Clock_Div; 			//时钟预分频
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_Period = Auto_Reload;				//自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //时钟分频1
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode =  TIM_OCMode_PWM2;   //选择定时器模式:PWM2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);				 //根据指定的参数初始化外设TIM3 OC2
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); //使能TIM3在CCR2上的预装载寄存器
}
/*---------------------------------------
 函数功能: 定时器3通道2初始化
 函数参数: 自动重装值Auto_Reload 0-65535
 调用示例: PWM_TIM3_CH2_Init(8000) 
----------------------------------------*/
void PWM_TIM3_CH2_Init(unsigned short int Auto_Reload)
{
	PWM_TIM3_CH2_Config( (7200000/Auto_Reload)-1 , 0);		
	TIM_Cmd(TIM3,ENABLE);	//使能TIM3
}
/*-------------------------------------------
 函数功能: 设定定时器3通道2的PWM频率和占空比
 函数参数: PWM频率freq 0-65535 Hz
 		   占空比 duty 0-65536 Hz
		   占空比频率 < PWM频率
 调用示例: PWM_TIM3_CH2_Set_FreqAndDuty(8000,4000); 
--------------------------------------------*/
void PWM_TIM3_CH2_Set_FreqAndDuty(unsigned short int freq,unsigned short int duty)
{
	PWM_TIM3_CH2_Init(freq);
	TIM_SetCompare2(TIM3,(720000/duty)-1);
}

	
