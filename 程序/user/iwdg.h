/*---------------------------------------------------------
		  独立看门狗(IWDG)配置驱动程序

 说明: 调用IWDG_Init()完成看门狗的配置,喂狗时间已经给出.
       使用十分简单,看门狗时钟在60—40kHz变动,所以喂狗时间
	   要留有余量,不然会导致反复复位动作.
	   通常配置:IWDG_Init(4,625) 喂狗时间为1000ms

 时间: 2014年2月8日		-BoX编写
---------------------------------------------------------*/
#ifndef __IWDG_H_
#define __IWDG_H_

void IWDG_Init(unsigned char prer,unsigned short int reload);
void IWDG_Feed(void);

#endif
