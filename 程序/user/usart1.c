/*---------------------------------------------------------
	      串口1 DMA接收配置程序
	说明: 串口配置程序需要包含stdarg.h方可使用
	      奋斗板接口PA10->RXD  PA9->TXD,USART1
		  使用printf的时候加\r\n方可输出回车键
		  USART1的接收DMA通道为5通道,发送DMA为4通道
    时间: 2014年1月22日 
---------------------------------------------------------*/
#include "stm32f10x.h"
#include "usart1.h"
#include "misc.h"
#include "stdarg.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "pincfg.h"

#include "task_main.h"
#include "task_sd.h"
#include "task_gui.h"
#include "task_sd.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;

unsigned char USART_Buffer[USART_BUFFER_SIZE];   //16字节串口缓冲区
/*-----------------------------------------
 函数功能: 配置串口1
------------------------------------------*/
void USART1_Config(void)
{
 	GPIO_InitTypeDef   IO_Init;
	USART_InitTypeDef  USART_InitStructure;
	DMA_InitTypeDef    DMA_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE);
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
	//A9复用推挽输出
	IO_Init.GPIO_Pin = GPIO_Pin_9;
	IO_Init.GPIO_Mode = GPIO_Mode_AF_PP;
	IO_Init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&IO_Init);
	
	//A10浮空输入
	IO_Init.GPIO_Pin = GPIO_Pin_10;
	IO_Init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&IO_Init);
	
	USART_InitStructure.USART_BaudRate = 256000;  			    //设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//八位数据位
	USART_InitStructure.USART_StopBits =  USART_StopBits_1;		//1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			//无校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //关硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	  //发送、接收模式
	USART_Init(USART1,&USART_InitStructure);  	 //写入配置
	USART_Cmd(USART1,ENABLE);				     //使能串口
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //使能接收中断
	
	DMA_DeInit(DMA1_Channel5); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;	   
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART_Buffer;		
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;		
    DMA_InitStructure.DMA_BufferSize = USART_BUFFER_SIZE;	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	 
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;  
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	   
    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	DMA_Init(DMA1_Channel5,&DMA_InitStructure); 	   
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);  //配置DMA接收完成后产生中断
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);   //串口接收时使用DMA
	DMA_Cmd(DMA1_Channel5,ENABLE);				   //使能DMA
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);	
}
/*---------------------------------------------------
 函数功能: 串口1 DMA传输完成中断服务
 函数说明: 每接收到USART_BUFFER_SIZE个字节产生1次中断
           在中断中解码数据并且完成相应动作,中断完成
		   时间＜1.5ms 完美解决先前把解码模块放在任务
		   切换中导致响应上位机命令速度慢的问题.
---------------------------------------------------*/
void DMA1_Channel5_IRQHandler(void)
{
	OSIntNesting++;
	if(DMA_GetITStatus(DMA1_IT_TC5) == SET)	 
	{
		DMA_Cmd(DMA1_Channel5,DISABLE);	    //缓冲区满关闭DMA防止缓冲区数据被覆盖			
		ReceiveDataFromPC();				//处理PC发来的数据
		DMA_ClearITPendingBit(DMA1_IT_TC5);
		DMA_Cmd(DMA1_Channel5,ENABLE);		//处理完成打开DMA		 
	}
	OSIntExit();	
}
/*------------------------------------------
 函数功能: 串口1中断服务程序(预留,现在啥也没做)
------------------------------------------*/
void USART1_IRQHandler(void)
{
   OSIntNesting++;
   if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)  //如果有接收中断且缓冲区没满
   {		
   		USART_ClearFlag(USART1,USART_IT_RXNE);  	   		   //清除中断位
   } 
   OSIntExit();	
}


/* 实现了printf函数的重定向作用 */
int fputc(int ch,FILE *f)
{
 	USART_SendData(USART1, (unsigned char) ch);	//调用stm32f10x_usart.c中的函数
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);  //等待发送完毕
	return ch;
}
/*---------------------------------------------------------
	函数功能: 自定义的类似printf功能函数
	函数参数: 需要发送数据的串口号USARTx
			  需要打印的数据data
	返回参数: 无
---------------------------------------------------------*/
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	
	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
				break;
				
				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
				break;
				
				default:
					Data ++;
				break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
					}
					Data++;
				break;
			
				case 'd':										//十进制
					d = va_arg(ap, int);
					itoa(d, buf, 10);
					for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
					}
					Data++;
				break;
			    default:  Data++;
				break;
			}		 
		} 
		else USART_SendData(USARTx, *Data++); //如果没遇到转意字符就正常输出
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}
/*--------------------------------------------------
	函数功能: 整形数据转换成字符串函数
	函数参数: 需要转换的整形数value
	          转换后的字符串 string
			  radix = 10
	函数返回: 无
---------------------------------------------------*/
static char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}
	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';
	    /* Make the value positive. */
	    value *= -1;
	}
	for (i = 10000; i > 0; i /= 10)	//把每整数的每一位分别格式化成字符
	{
	    d = value / i;
	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}
	/* Null terminate the string. */
	*ptr = 0;
	return string;
}
