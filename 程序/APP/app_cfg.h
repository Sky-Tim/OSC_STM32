/*------------------------------------------------------------------------------------
        		   STM32 UCOS-II 多任务工程模板(USART)
 说明: 写APP请在app.c完成,写与硬件相关的驱动请在bsp.c完成并且定义相应的头文件,并且写入
 	   includes.h中.本模板是已经完成UCOS-II在STM32上的移植,可以根据项目的不同裁剪内核
	   大小来完成,请在os_cfg.h完成裁剪.本工程自带3个LED显示1个串口发送的多任务执行.
	   
	   创建一个任务的步骤:								
	   *(1) 在app_cfg.h设置任务优先级和栈大小,也就是宏定义。
	   *(2) 在main文件中定义任务栈 OS_STK task_led1_stk[TASK_LED1_STK_SIZE]。
	   *(3) 在app.c中定义任务的具体内容要干什么,也就是写一个函数模块,记住还要在app.h中声明函数.
	   *(4) 在main函数中创建任务 OSTaskCreate(Task_LED1,(void *)0,&task_led1_stk[TASK_LED1_STK_SIZE-1], TASK_LED1_PRIO);
	   *(5) 编译运行即可完成一个任务的创建。

 时间: 2013年8月19日       BoX编写
-------------------------------------------------------------------------------------*/
#ifndef __APP_CFG_H
#define __APP_CFG_H

/*******************设置任务优先级*******************/   
#define TASK_LED1_PRIO          4
#define TASK_LED2_PRIO          3
#define TASK_LED3_PRIO          2
#define TASK_USART_PRIO         1           
 
/************设置栈大小（单位为 OS_STK ）************/   
#define TASK_LED1_STK_SIZE      80 
#define TASK_LED2_STK_SIZE	    80
#define TASK_LED3_STK_SIZE	    80
#define TASK_USART_STK_SIZE     80

#endif
