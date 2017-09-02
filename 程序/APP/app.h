/*------------------------------------------------------------------------------------
        		   		STM32+UCOS+UCGUI示波器
 说明: 写APP请在app.c完成,本模板是已经完成UCOS-II在STM32上的移植,可以根据项目的不同裁剪内核
	   大小来完成,请在os_cfg.h完成裁剪.本工程自带3个LED显示1个串口发送的多任务执行.
	   
	   创建一个任务的步骤:								
	   *(1) 在app.h设置任务优先级和栈大小,也就是宏定义。
	   *(2) 在main文件中定义任务栈 OS_STK task_led1_stk[TASK_LED1_STK_SIZE]。
	   *(3) 在app.c中定义任务的具体内容要干什么,记住还要在app.h中声明函数、宏定义栈大小、宏定义优先级
	   *(4) 在main函数中创建任务 
	        OSTaskCreate(Task_LED1,(void *)0,&task_led1_stk[TASK_LED1_STK_SIZE-1], TASK_LED1_PRIO);
	   *(5) 编译运行即可完成一个任务的创建。

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
#ifndef _APP_H_    
#define _APP_H_    
   
/*******************设置任务优先级*******************/ 
#define TASK_START_PRIO				   5  
#define TASK_MAIN_PRIO                 11
#define TASK_RTC_PRIO                  12
#define TASK_SD_PRIO                   13
#define TASK_TOUCHSCREEN_PRIO          14
#define TASK_GUI_PRIO                  15           
 
/************设置栈大小（单位为 OS_STK ）************/   
#define TASK_GUI_STK_SIZE              1024
#define TASK_MAIN_STK_SIZE	           2048
#define TASK_RTC_STK_SIZE	           512
#define TASK_SD_STK_SIZE               512
#define TASK_TOUCHSCREEN_STK_SIZE      256
#define TASK_START_STK_SIZE				64 

/**************** 用户任务声明 **********************/   
void Task_TouchScreen(void *pdata);
void Task_Main(void *pdata); 
void Task_RTC(void *pdata);
void Task_SD(void *pdata); 
void Task_GUI(void *pdata);
void Task_Start(void *pdata);

  
    
#endif  //_APP_H_
