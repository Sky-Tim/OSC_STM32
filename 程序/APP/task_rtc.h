#ifndef __TASK_RTC_H__
#define __TASK_RTC_H__

//日历的数据结构
typedef struct 
{
	unsigned char hour;
	unsigned char min;
	unsigned char sec;			
	unsigned short int w_year;
	unsigned char  w_month;
	unsigned char  w_date;
	unsigned char  week;		 
}CalendarType;	

void RTC_Init(void);
void RTC_NVIC_Config(void);
void RTC_Config(void);
void Set_RTC_Time_Manual(unsigned int shi,unsigned int fen,unsigned int miao);
void Display_RTC_Time(void);
unsigned char Is_Leap_Year(unsigned short int year);
unsigned char RTC_Set_Time(unsigned short int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);
unsigned char RTC_Get_Time(CalendarType *calendar);
unsigned char RTC_Get_Week(unsigned short int year,unsigned char month,unsigned char day);

#endif
