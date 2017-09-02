/*---------------------------------------------------------
		  独立看门狗(IWDG)配置驱动程序

 说明: 调用IWDG_Init()完成看门狗的配置,喂狗时间已经给出.
       使用十分简单,看门狗时钟在60—40kHz变动,所以喂狗时间
	   要留有余量,不然会导致反复复位动作.
	   通常配置:IWDG_Init(4,625) 喂狗时间为1000ms

 时间: 2014年2月8日		-BoX编写
---------------------------------------------------------*/
#include "iwdg.h"
#include "stm32f10x.h"
/*-------------------------------------------
 函数功能:初始化独立看门狗
 
 函数参数:prer   - 分频数0~7
 		  reload - 重装载寄存器值
 
 函数说明:分频因子    = 4*2^prer
          喂狗时间(ms)= ((4*2^prer)*reload)/40
--------------------------------------------*/
void IWDG_Init(u8 prer,u16 reload) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64	
	IWDG_SetReload(reload);   //设置IWDG重装载值	
	IWDG_ReloadCounter();     //按照IWDG重装载寄存器的值重装载IWDG计数器	
	IWDG_Enable();  		  //使能IWDG
}
/*-------------------------------------------
 函数功能:调用函数完成喂狗
--------------------------------------------*/
void IWDG_Feed(void)
{   
 	IWDG->KR = 0xAAAA;										   
}