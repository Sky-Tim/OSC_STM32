/*---------------------------------------------------------
		  		示波器基本功能模块子程序

 说明: 本程序完成示波器最基本的功能,包括增益的设置,时基的
 	   设置,波形的显示,获取波形的频率周期.还有信号发生器的
	   设置.

	   定义了3个十分重要的结构体,分别是

	   1) WaveMode结构体主要完成示波器显示波形的一些配置参数
	   2) WaveType结构体主要完成波形电参量和时间参量的储存,注意修饰符volatile
	   3) FG_WaveType结构体主要完成信号发生器参量信息的储存
	   4) FunctionGeneratorType枚举类型为了防止错误的赋值

	   因为采用CD4051模拟开关,存在增益配置的排列组合,所以
	   手工完成了增益的排列组合表,根据具体的硬件不同修改

 时间: 2014年2月8日		-BoX编写
---------------------------------------------------------*/
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "pincfg.h"
#include "tft_api.h"
#include "dac.h"
#include "stdio.h"

#include "task_main.h"
#include "task_gui.h"

/*-----------------------------------------
		    	声明变量
 说明: WaveTab数组作为查表法产生波
------------------------------------------*/
unsigned int   IntFullTime=0; 		//测量矩形波TIM5中断溢出次数

extern uint16_t SineWaveTab[32];	 //32个点正弦波表
extern uint16_t TriangleWaveTab[32];
extern uint16_t SquareWaveTab[32];
extern uint16_t SawtoothWaveTab[32];
extern uint16_t AnyWaveTab[32];
extern uint8_t  InterruptTimes;

extern WaveType 	WaveInfo;
extern WaveMode 	WaveCtrl;
extern FG_WaveType  FG_WaveInfo;
/*-------------------------------------------
 函数功能: 自动扫描合适增益
 返回值  : float型扫描增益
 调用示例: AutoGain = GainScan();
-------------------------------------------*/
float AutoGainScan(void)
{
 	unsigned char i;
	float gain;
	for(i=1;i<=14;i++)
	{
	 	switch(i)	  //每段增益扫描间隔250ms以防继电器来不及开关
		{
			case 1:   GAINX0_05;  gain = 0.05;OSTimeDlyHMSM(0,0,1,250);break;
			case 2:   GAINX0_1;	  gain = 0.1; OSTimeDlyHMSM(0,0,1,250);break;
			case 3:   GAINX1;	  gain = 1.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 4:   GAINX2;	  gain = 2.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 5:   GAINX4;	  gain = 4.0; OSTimeDlyHMSM(0,0,1,250);break;
			case 6:   GAINX10;	  gain = 10.0;OSTimeDlyHMSM(0,0,1,250);break;
			case 7:   GAINX25;	  gain = 25.0;OSTimeDlyHMSM(0,0,1,250);break;
			default:  break;
		}
		ShowRealTimeWave();
		if(WaveInfo.Vmax>=2.40 && WaveInfo.Vmax<=3.3 && WaveInfo.Vmin<1.0) //如果采集到的AD处于合适的档位
		{
//			GainControl(gain);
			return gain;  //返回增益值
		}	
	}
	return 0.0;  //如果执行完14次扫描都没有成功
}

void ManualGainScan(unsigned int gain)
{
	switch(gain)	  //每段增益扫描间隔250ms以防继电器来不及开关
	{
		case 1:   GAINX0_05;  LCD_Write_String(300,230,"X0.05 ",Yellow,Black);
				  break;
		case 2:   GAINX0_1;	  LCD_Write_String(300,230,"X0.1  ",Yellow,Black);
				  break;
		case 3:   GAINX1;	  LCD_Write_String(300,230,"X1.0  ",Yellow,Black);
				  break;
		case 4:   GAINX2;	  LCD_Write_String(300,230,"X2.0  ",Yellow,Black);
				  break;
		case 5:   GAINX4;	  LCD_Write_String(300,230,"X4.0  ",Yellow,Black);
			      break;
		case 6:   GAINX5;	  LCD_Write_String(300,230,"X5.0  ",Yellow,Black);
				  break;
		case 7:   GAINX10;	  LCD_Write_String(300,230,"X10.0 ",Yellow,Black);
				  break;
		case 8:   GAINX25;	  LCD_Write_String(300,230,"X25.0 ",Yellow,Black);
			      break;
		default:  break;
	}   
}

/*-----------------------------------------------
	函数功能: 获取矩形波周期
	当前性能: 测量频率范围300Hz~200KHz
	          测量周期范围3.3ms~5us
-----------------------------------------------*/
unsigned int GetSquareWavePriod(void)
{
	unsigned int temp;
	temp = IntFullTime * 2000;
	temp += (unsigned int)TIM_GetCounter(TIM5);
    IntFullTime = 0;
	TIM_SetCounter(TIM5,0);
	InterruptTimes = 0;
	EXTI->IMR |= EXTI_Line0;	//开启外部中断0
	return temp;
}
/*-----------------------------------------------
 函数功能: 函数发生器
 函数参数: ft   - 函数类型
 		   feq  - 频率(Hz)
		   amp  - 振幅(V)
		   duty - 占空比(%)
-----------------------------------------------*/
void FunctionGenerator(FunctionGeneratorType ft,uint32_t feq,float amp,uint8_t duty)
{
	DAC_InitTypeDef  DAC_InitStructure;
	char i,iH;
		
	DACTriggerByTIM2(2250000/feq,0);   //设定触发频率
		
	if(ft == Triangle_Wave)			   //修改标准波形的幅值存入数组
	{
		for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * TriangleWaveTab[i]);
		FG_StartOutput(AnyWaveTab);	   //开始输出		
	}

	if(ft == Square_Wave)
	{	
		iH = (32.0 * (duty / 100.0));  //计算占空比在波形表的下标数
		for(i=iH; i<32; i++)		   //填充高电平
			AnyWaveTab[i] = (u16)((amp / 3.3) * 4095);
		for(i=0; i<iH; i++)		       //填充低电平
			AnyWaveTab[i] = 0;
		FG_StartOutput(AnyWaveTab);
	}
		
	if(ft == Sine_Wave)
	{		
		for(i=0; i<32; i++)
			AnyWaveTab[i] = SineWaveTab[i];
		for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * SineWaveTab[i]);
		FG_StartOutput(AnyWaveTab);	
	}

	if(ft == Sawtooth_Wave)
	{
	 	for(i=0; i<32; i++)
			AnyWaveTab[i] = (u16)((amp / 3.3) * SawtoothWaveTab[i]);
		FG_StartOutput(AnyWaveTab);
	}
	//噪声硬件输出
	if(ft == Noise_Wave)
	{
	 	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;  //DAC转换由TIM2更新来触发
		DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;	//产生噪声
		DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095; 
		DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	    DAC_Init(DAC_Channel_1,&DAC_InitStructure);
		DAC_Cmd(DAC_Channel_1,ENABLE);
	}		
}
/*-----------------------------------------------
 函数功能: 载入波形表开始输出波形
 函数参数: WaveTab[] - 32点波形表数据数组
-----------------------------------------------*/
void FG_StartOutput(uint16_t WaveTab[])
{	
	DMA_InitTypeDef DMA_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	
	DAC_DMACmd(DAC_Channel_1,DISABLE);
	DAC_Cmd(DAC_Channel_1,DISABLE);
	DMA_Cmd(DMA2_Channel3,DISABLE);
	
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = 0;	 //不能省,否则不工作
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40007408;//DAC_DHR12R1寄存器地址(查手册)
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)WaveTab;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 32;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);
	
	DMA_Cmd(DMA2_Channel3, ENABLE);	
	DAC_Cmd(DAC_Channel_1, ENABLE);	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}
/*-----------------------------------------------
 函数功能: 时基控制
 函数参数: 时基参数(预分频系数)
-----------------------------------------------*/
void TimeBaseControl(uint16_t TimeBASE)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 1;          
	TIM_TimeBaseStructure.TIM_Prescaler = TimeBASE;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	
}

