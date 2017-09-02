/*-------------------------------------------------------------------------------------------
 			                   STM32示波器主任务
 
 说明: 示波器主任务完成了获取频率周期等时间参量和电参量并且完成计算,是核心任务,优先级最高
 	   加入了上位机程序,产生了上位机和下位机进行通讯的问题,自定义了通信协议,每一帧长度16Byte
	   由命令帧和数据帧组成,帧头和帧尾作为校验码.详细通信协议的制定写在《STM32示波器通信协议》
	   Excel表格中.如何对数据进行有效编码和解码同时又要具有较高的传输效率是比较头疼的问题,限于
	   目前的水平采用了较为简单的ASCII编码协议技术,同时为了快速响应上位机命令,把解码模块放在
	   ISR中完成,响应速度小于1.5ms,同时对传输错误的帧如何处理也是一个有趣的问题.
	   经过计算,自定义的通信协议有效传输速率理论最大可达16000bps,实际采用10666bps.

 版本: v1.0 2013/11/30 	最初原始版本  
 	   v3.0 2014/2/18   基本完成版本    
  
 BoX编写   
-------------------------------------------------------------------------------------------*/
#include "task_main.h"
#include "task_gui.h"
#include "task_sd.h"

#include "stdio.h"
#include "stdlib.h"
#include "ucos_ii.h"
#include "pincfg.h"
#include "delay.h"
#include "tft_api.h"
#include "indkey.h"
#include "timer.h"
#include "EXTI.H"
#include "adc.h"
#include "usart1.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern OS_EVENT *LCD_Buffer_MUTEX;
extern OS_EVENT *USART_Buffer_MUTEX;
extern OS_EVENT *SDtoRAM_Buffer_MUTEX;

extern uint8_t LCD_Buffer[LCD_BUFFER_SIZE];
extern uint8_t USART_Buffer[USART_BUFFER_SIZE];
extern volatile uint16_t ADCConvertedValue[SAMPDEPTH];

WaveType 	WaveInfo;
WaveMode 	WaveCtrl;
FG_WaveType FG_WaveInfo;	//信号发生器参数

/*-----------------------------------------
 函数说明:初始化波形配置参数
------------------------------------------*/
void WaveMode_Init(WaveMode* WaveCtrl)
{
    WaveCtrl->UpdatTrue = 0;
    WaveCtrl->TriggerMode = Trigger_Rising;
	WaveCtrl->TimeBase = 99;
	WaveCtrl->Gain = 3;
}
/*-----------------------------------------
 函数说明:任务堆栈检查 
------------------------------------------*/
void TaskStackChack(void)
{
	OS_STK_DATA data;
	uint8_t i,err;
	for(i=0;i<5;i++)	  //当前工程有5个任务
	{
	 	OSTaskStkChk(11+i,&data);
		LCD_Write_String(30,20,"Prio Total Free Used ",Green,Black);

		OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量		
		sprintf(LCD_Buffer," %2d  %2d  %2d  %2d ",  11+i,
													 data.OSFree+data.OSUsed,
													 data.OSFree,
													 data.OSUsed);
		LCD_Write_String(30,40+20*i,LCD_Buffer,Green,Black);		
		OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量
	}
}
/*-----------------------------------------
 函数说明:获取频率周期值,通过调用oscilloscope.c
          中的GetSquareWavePriod()得到
------------------------------------------*/
void GetFrequence(void)
{	
	//完成周期测量和频率计算		
    WaveInfo.Priod = GetSquareWavePriod();
	WaveInfo.Frequency = 1000000 / WaveInfo.Priod;
	
	//完成高电平测量和占空比计算
	WaveInfo.HighWidth = WaveInfo.Priod - WaveInfo.LowWidth;
	WaveInfo.DutyCycle = WaveInfo.HighWidth*100 / WaveInfo.Priod;		
}

/*-----------------------------------------
 函数说明:获取AD FIFO中的原始值且显示
------------------------------------------*/
void GetWaveADCValue(void)
{
	if(WaveCtrl.UpdatTrue == 1 && WaveCtrl.Stop == 0)
	{
		WaveCtrl.UpdatTrue = 0;		
		ShowRealTimeWave();
//		SD_SaveWaveADValue();		//存储波形
//		WaveCtrl.SavedSD = 0;			
		EXTI->IMR |= EXTI_Line1;	//开启AD下一轮转换	
	}
}
/*------------------------------------------------------
 函数说明:上位机发送数据到MCU,由MCU负责解码
 注意事项:先对数据流解码,区分命令和数据,再参照命令表编写
		  命令动作.本程序为了加快响应速度没有采取加大缓
		  冲区的方式,而是放在DMA传输完成中断中处理,解码
		  处理时间大约1毫秒.
--------------------------------------------------------*/
void ReceiveDataFromPC(void)
{
	INT8U err,JieMaOK=0;		//解码OK标志位
	uint32_t Cmd_Data,Value;
	
	JieMaOK = PCtoMCU_Decoding(USART_Buffer,&Cmd_Data,&Value); //对数据流解码
	
	if(Cmd_Data>100 && Cmd_Data<200 && JieMaOK==1) //收到的是命令(见示波器命令表)
	{
	 	switch(Cmd_Data)
		{
			//基本控制类命令
		 	case 101: printf("STOP/RUN\r\n");
					  WaveCtrl.Stop = !WaveCtrl.Stop;
					  break;
		
			case 102: printf("回显波形\r\n");
					  ShowSavedWave();
					  break;
			
			case 103: printf("保存波形\r\n");
					  break;

			case 104: printf("AC\r\n");
					  JDQ_ACDC = 1;		  		//交流耦合
					  break;

			case 105: printf("DC\r\n");	  	
					  JDQ_ACDC = 0;		  		//直流耦合
					  break;
		    
			//增益控制类命令
			
			case 111: printf("设置增益\r\n");
					  if(Value>0 && Value<9)	//确保数据正确
					  	WaveCtrl.Gain = Value;
			          ManualGainScan(WaveCtrl.Gain);
					  break;
			
			case 112: printf("增益增大\r\n");				  	  
	   		          if(++WaveCtrl.Gain > 8)
	   					WaveCtrl.Gain = 1;
					  ManualGainScan(WaveCtrl.Gain);
					  break;
			
			case 113: printf("增益减小\r\n");				      
	   				  if(--WaveCtrl.Gain < 1)
	   					WaveCtrl.Gain = 8;
					  ManualGainScan(WaveCtrl.Gain);
					  break;
		
			case 114: printf("自动增益\r\n");
					  break;
			
			//时基控制类命令
			
			case 121: printf("设置时基为:%d\r\n",Value);
					  if(Value>=0 && Value<=1000)  //确保数据正确
					  	WaveCtrl.TimeBase = Value;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 122: printf("时基增大\r\n");					  
					  WaveCtrl.TimeBase += 5;
					  if(WaveCtrl.TimeBase >= 1000)
					  	WaveCtrl.TimeBase = 1000;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 123: printf("时基减小\r\n");
					  WaveCtrl.TimeBase -= 5;									  
					  if(WaveCtrl.TimeBase <= 1)
					  	WaveCtrl.TimeBase = 1;
					  TimeBaseControl(WaveCtrl.TimeBase);
					  break;
			
			case 124: printf("自动时基\r\n");
					  break;
			
			//波形发生器类命令
			
			case 131: printf("三角波\r\n");
				      FunctionGenerator(Triangle_Wave,FG_WaveInfo.Frequency,
					  								  FG_WaveInfo.Vpp,
					  								  FG_WaveInfo.DutyCycle);
					  break;
			case 132: printf("矩形波\r\n");
					  FunctionGenerator(Square_Wave,FG_WaveInfo.Frequency,
					  								FG_WaveInfo.Vpp,
					  								FG_WaveInfo.DutyCycle);
					  break;
			case 133: printf("正弦波\r\n");
					  FunctionGenerator(Sine_Wave,FG_WaveInfo.Frequency,
					  							  FG_WaveInfo.Vpp,
					  							  FG_WaveInfo.DutyCycle);
					  break;
			case 134: printf("白噪声\r\n");
					  FunctionGenerator(Noise_Wave,FG_WaveInfo.Frequency,
					  							   FG_WaveInfo.Vpp,
					  							   FG_WaveInfo.DutyCycle);
					  break;
			case 135: printf("扫频\r\n");
					  break;
			
			//信号分析类命令
		
			case 141: printf("FFT\r\n");				 
					  break;
			case 142: printf("频谱\r\n");
					  break;
			case 143: printf("功率谱\r\n");
					  break;
			case 144: printf("交流\r\n");
					  break;
			case 145: printf("直流\r\n");
					  break;

			 default: break;
		}
	}
	
	if(Cmd_Data>1000 && Cmd_Data<2000 && JieMaOK==1) //收到的是数据(见示波器命令表)	
	{
	 	switch(Cmd_Data)
		{
			//接收波形发生器参数
		 	case 1301: FG_WaveInfo.Frequency = Value; break; 
			case 1302: FG_WaveInfo.Vpp = Value/10.0;  break;//上位机把浮点型×10倍,要÷回来
			case 1303: FG_WaveInfo.DutyCycle = Value; break;
			default  : break;
		}
	}
}
/*----------------------------------------------------------
 函数说明:对上位机发来的数据进行解码,解码依据请参照协议表
 函数参数:Revdata[] - 指向需要解码的缓冲区
 		  CmdorData - 指向INT32U类型指针,存放命令,数据指令
 		  value     - 指向INT32U类型指针,存放数据帧
 返 回 值:解码成功返回1,解码失败(误码)返回0
 调用示例:JieMaOK = PCtoMCU_Decoding(USART_Buffer,&Cmd_Data,&Value);
          本程序为了加快响应速度没有采取加大缓冲区的方式,而是放在
		  DMA传输完成中断中处理,解码处理时间大约1毫秒.
----------------------------------------------------------*/
uint8_t PCtoMCU_Decoding(uint8_t Revdata[],uint32_t *CmdorData,uint32_t *value)
{
	uint8_t j,k,m,i;
	uint8_t data[10];				//解码临时存储区	
	
	if(Revdata[0]=='(' && Revdata[15]==')' )//帧头-帧尾
	{	
	 	if(Revdata[1] == 'C') 	 //CMD
		{
			data[0] = 0x43;
			printf("CMD ");
		}	   		 
		if(Revdata[1] == 'D') 	 //DATA
		{
			data[0] = 0x44;
			printf("DATA ");
		}
//			for(i=0;i<16;i++)printf("%c",USART_Buffer[i]);printf("\r\n");
		j = 2;
		k = 1;
		while(Revdata[j] != 'a' && Revdata[j]>='0' && Revdata[j]<='9')	//没遇到a之前
		{
			data[k] = Revdata[j];
			k++;
		 	j++;
			if(k>10) break;		//防止进入死循环
		}
		*CmdorData = atoi(&data[1]);  //从数据位开始检索,接收CMD或DATA			
		for(m=0; m<10; m++)    	//data长度为10
				data[m] = ' ';	//清空data缓冲用0x20填满
		k = 0;
		j++;
		while(Revdata[j] != 'b' && Revdata[j]>='0' && Revdata[j]<='9')
		{
			data[k] = Revdata[j];
			k++;
		 	j++;
			if(k>10) break;		//防止进入死循环
		}		 
		*value = atoi(data);	//接收数据
		for(m=0; m<10; m++)    	//data长度为10
				data[m] = ' ';	//清空data缓冲用0x20填满
	}
	else						
	{							
		printf("DataError\r\n");//如果发现传输错误则重置串口和DMA
		USART_Buffer[0] = '(';	//向串口缓冲写入正确的帧头帧尾
		USART_Buffer[15]= ')';
		USART_Buffer[1] = 'E';	//同时写入E(Error)表明错误帧
		
		USART1_Config();		//此语句对于提高系统稳定性十分重要
		return 0;				
	}
	return 1;							 //解码完成	 	
}
/*-----------------------------------------
 函数说明:对发往上位机的数据进行编码
 函数参数:
------------------------------------------*/
void MCUtoPC_Coding(uint8_t data[])
{

}
/*-----------------------------------------
 函数说明:串口发送波形参数到上位机
------------------------------------------*/
void SendDataToPC(void)
{
	OS_CPU_SR  cpu_sr = 0u;
	INT8U err;
	
	if(WaveCtrl.Stop != 1)	 //如果按下STOP则停止发送数据到上位机
	{
		OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
		/* Start(S)-(data)-A-(data)-B-(data)-C-(data)-D-(data)-ect. */
		sprintf(LCD_Buffer," %dA%dB%dC%dD%dE%.2fF%.2fG%.2fH%.2fI%2dJ" 
											  ,WaveInfo.Frequency
											  ,WaveInfo.Priod
										      ,WaveInfo.HighWidth
										      ,WaveInfo.LowWidth
											  ,WaveInfo.DutyCycle
											  ,WaveInfo.Vmax
											  ,WaveInfo.Vmin
											  ,WaveInfo.Vpp
											  ,WaveInfo.Vrms
											  ,GetTempSensor());
		//数据发送时不希望被打断
		OS_ENTER_CRITICAL();
		printf("%s\r\n",LCD_Buffer);
		OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量	
		OS_EXIT_CRITICAL();
	}			
}