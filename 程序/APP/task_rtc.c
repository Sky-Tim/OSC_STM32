/*-------------------------------------------------------------------------------------------
 			                   STM32示波器实时时钟任务
 
 说明: 实时时钟任务使用STM32自带的时钟完成,如何从秒计算出日期时间是纯算法问题,很简单无需多讲
 	   多看看历法规则就OK

 版本: v1.0 2013/11/27 	最初原始版本      
  
 BoX编写   
-------------------------------------------------------------------------------------------*/
#include "task_rtc.h"
#include "task_main.h"
#include "stdio.h"
#include "ucos_ii.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "oscilloscope.h"
#include "indkey.h"
#include "timer.h"
#include "EXTI.H"
#include "misc.h"
#include "stm32f10x.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern uint8_t LCD_Buffer[LCD_BUFFER_SIZE];
extern OS_EVENT *LCD_Buffer_MUTEX;
extern OS_EVENT *USART_Buffer_MUTEX;
extern OS_EVENT *SDtoRAM_Buffer_MUTEX;

const uint8_t table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
CalendarType calendar;									//日历的数据结构
/*-------------------------------------------
	函数功能: RTC初始化
	函数参数: 无	
-------------------------------------------*/
void RTC_Init(void)
{
	RTC_NVIC_Config();				  			  //给时钟配置中断
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x1234) //如果没有配置过时钟
	{
		RTC_Config();
		BKP_WriteBackupRegister(BKP_DR1,0x1234);  //写入1234表示已经配置过,下次不用配置
	}
	else								  
	{
		RTC_WaitForSynchro();  			  //等待时钟同步
		RTC_ITConfig(RTC_IT_SEC,ENABLE);  //使能秒中断
		RTC_WaitForLastTask();            //等待寄存器操作完成
	}
//	RTC_Set_Time(2014,2,14,23,0,0);
	RCC_ClearFlag(); 					 //清除RCC重启标志
} 
/*-------------------------------------------
	函数功能: RTC配置外设值
	函数参数: 无	
-------------------------------------------*/
void RTC_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);  			//使能备份区后备寄存器访问
	BKP_DeInit();				  			//复位备份区域
	RCC_LSEConfig(RCC_LSE_ON);	  			//开启外部低速时钟振荡器
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //选择LSE作为RTC时钟
	RCC_RTCCLKCmd(ENABLE);		  	   		//使能RTC时钟
	RTC_WaitForSynchro();		  	   		//等待和APB1时钟同步完成
	RTC_WaitForLastTask();		  	   		//等待刚才的操作完成
	RTC_ITConfig(RTC_IT_SEC, ENABLE);  		//使能秒中断
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767); 
	RTC_WaitForLastTask();
}
/*-------------------------------------------
	函数功能: RTC中断配置
	函数参数: 无	
-------------------------------------------*/
void RTC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVICInit;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVICInit.NVIC_IRQChannel = RTC_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2; 
    NVICInit.NVIC_IRQChannelSubPriority = 2;  		
	NVICInit.NVIC_IRQChannelCmd = ENABLE;	  
	NVIC_Init(&NVICInit); 	
}
/*-------------------------------------------
	函数功能: RTC时钟手动设置
	函数参数: 时shi,分fen,秒miao	
-------------------------------------------*/
void Set_RTC_Time_Manual(unsigned int shi,unsigned int fen,unsigned int miao)  //手动设定时间
{
	unsigned int temp;
	temp = shi*3600 + fen*60 + miao;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);    				 
    RTC_SetCounter(temp);		
    RTC_WaitForLastTask();		   
}
/*-------------------------------------------
	函数功能: 打印出时间值
	函数参数: 无	
-------------------------------------------*/
void Display_RTC_Time(void)
{
	INT8U err;
	
	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
	sprintf(LCD_Buffer,"%d-%d-%d",calendar.w_year,
								   calendar.w_month,
								   calendar.w_date);
	LCD_Write_String(300,250,LCD_Buffer,Yellow,Black);
	OSMutexPost(LCD_Buffer_MUTEX);			  //释放信号量
	if(calendar.min<10)
	{
		OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
		sprintf(LCD_Buffer,"%d:0%d",calendar.hour,calendar.min);
		LCD_Write_String(340,230,LCD_Buffer,Yellow,Black);
		OSMutexPost(LCD_Buffer_MUTEX);	
	}
	else
	{
	 	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
		sprintf(LCD_Buffer,"%d:%d",calendar.hour,calendar.min);
		LCD_Write_String(340,230,LCD_Buffer,Yellow,Black);
		OSMutexPost(LCD_Buffer_MUTEX);
	}

}
/*----------------------------------------------
			判断是否是闰年
	月份   1  2  3  4  5  6  7  8  9  10 11 12
	闰年   31 29 31 30 31 30 31 31 30 31 30 31
	非闰年 31 28 31 30 31 30 31 31 30 31 30 31
	输入:年份
	输出:该年份是不是闰年.1,是.0,不是
----------------------------------------------*/
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) 		
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)
				return 1; 	   
			else 
				return 0;   
		}
		else 
			return 1;   
	}
	else 
		return 0;	
}	 			   
/*------------------------------------------------
					设置时钟
 把输入的时钟转换为秒钟,以1970年1月1日为基准
 1970~2099年为合法年份
 返回值:0,成功;其他:错误代码.
-------------------------------------------------*/										 
uint8_t RTC_Set_Time(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint16_t t;
	uint32_t seccount=0;
	if(syear<1970||syear>2099)
		return 1;	   
	for(t=1970;t<syear;t++)				//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))
			seccount+=31622400;			//闰年的秒钟数
		else 
			seccount+=31536000;			//平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   				//把前面月份的秒钟数相加
	{
		seccount+=(uint32_t)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)
			seccount+=86400;			//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(uint32_t)(sday-1)*86400; //把前面日期的秒钟数相加 
	seccount+=(uint32_t)hour*3600;	    //小时秒钟数
    seccount+=(uint32_t)min*60;	 		//分钟秒钟数
	seccount+=sec;						//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	
	PWR_BackupAccessCmd(ENABLE);		//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);			//设置RTC计数器的值
	RTC_WaitForLastTask();		
	return 0;	    
}
/*----------------------------------------
			得到当前的时间
 返回值:0,成功;其他:错误代码.
 调用示例:RTC_Get_Time(&calendar); 
-----------------------------------------*/
uint8_t RTC_Get_Time(CalendarType *calendar)
{
	static uint16 daycnt=0;
	uint32 timecount=0; 
	uint32 temp=0;
	uint16 temp1=0;	  
 	
	timecount = RTC->CNTH;		//得到计数器中的值(秒钟数)
	timecount <<= 16;
	timecount += RTC->CNTL;			 
 	temp=timecount/86400;   	//得到天数(秒钟数对应的)
	if(daycnt!=temp)			//超过一天了
	{	  
		daycnt=temp;
		temp1=1970;				//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)
					temp-=366;	//闰年的秒钟数
				else 
				{	temp1++;
					break;
				}  
			}
			else 
				temp-=365;	  	//平年 
			temp1++;  
		}   
		calendar->w_year=temp1;	//得到年份
		temp1=0;
		while(temp>=28)			//超过了一个月
		{
			if(Is_Leap_Year(calendar->w_year)&&temp1==1)	//当年是不是闰年/2月份
			{
				if(temp>=29)
					temp-=29;	//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])
					temp-=mon_table[temp1];		//平年
				else 
					break;
			}
			temp1++;  
		}
		calendar->w_month=temp1+1;	//得到月份
		calendar->w_date=temp+1;  	//得到日期 
	}
	temp=timecount%86400;     		//得到秒钟数   	   
	calendar->hour=temp/3600;     	//小时
	calendar->min=(temp%3600)/60; 	//分钟	
	calendar->sec=(temp%3600)%60; 	//秒钟
	calendar->week = RTC_Get_Week(calendar->w_year,calendar->w_month,calendar->w_date);	//获取星期   
	return 0;
}	 
/*----------------------------------------------------
				获得现在是星期几
 输入公历日期得到星期(只允许1901-2099年)
 输入参数：公历年月日 
 返回值：星期号
-----------------------------------------------------*/																						 
uint8 RTC_Get_Week(uint16 year,uint8 month,uint8 day)
{	
	uint16 temp2;
	uint8 yearH,yearL;
	
	yearH=year/100;					// 如果为21世纪,年份数加100
	yearL=year%100; 	  
	if (yearH>19)
		yearL+=100;		// 所过闰年数只算1900年之后的
	  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)
		temp2--;
	return(temp2%7);
}
/*-------------------------------------------
	实时时钟中断服务程序,根据实际需要编写
	粘贴到stm32f10x_it.c即可使用,十分方便	
-------------------------------------------*/
void RTC_IRQHandler(void)
{
	OSIntNesting++;
	if(RTC_GetITStatus(RTC_IT_SEC) != RESET)				 //读取秒中断状态
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);					 //清除秒中断标志	  
		RTC_WaitForLastTask();
		RTC_Get_Time(&calendar);							 //10s更新一次时间
		if(calendar.sec%10 == 0)
			Display_RTC_Time();	  							   
	}
	OSIntExit();	
}

		