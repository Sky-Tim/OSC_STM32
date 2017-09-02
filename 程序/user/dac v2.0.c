/*------------------------------------------------------------------------------------------
		    				STM32 DAC配置驱动程序(v2.0)
 
 说明: 1) STM32内部自带2个12位DAC,电压输出型.本程序启用了其中的DAC1通道输出电压.转换范围从
          0~Vref,奋斗板接法PA4->DAC1  PA5->DAC2,使用方法简单,拿来就用.使用TIM2作为触发更新
		  源触发DAC1产生三角波.

	   2) V2.0舍弃了硬件产生三角波,改用查表法结合DMA产生正弦波,三角波,矩形波等等,功能更加
	      强大好用,使用了DMA2通道3,和DAC1.注意!本驱动程序和sdcard.c存在冲突,同时使用可能导
		  致死机.SDIO的DMA使用的是DMA2通道4,DAC2-DMA使用的也是DMA2通道4
		  频率计算公式:
		  Feq=72MHz/(TIM_Prescaler+1)/TIM_Period/波形点数
 
 时间: 2014年2月5日    BoX编写
 版本: V1.0-产生三角波验证通过
       V2.0-查表法产生任波形 
-----------------------------------------------------------------------------------------*/
#include "dac.h"
#include "stm32f10x.h"
/*--------------------------
 	  1个周期32点波形表
--------------------------*/
uc16 SineWaveTab[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      	3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 
                      	599 , 344 , 155 , 38,0, 38, 155, 344, 599, 909, 1263, 1647};

uc16 TriangleWaveTab[32] = {0,255,511,767,1023,1279,1535,1791,2047,2303,2559,2815,3071,3327,3583,3839,4095,
							3839,3583,3327,3071,2815,2559,2303,2047,1791,1535,1279,1023,767,511,255};

uc16 SawtoothWaveTab[32] = {127,255,383,511,639,767,895,1023,1151,1279,1407,1535,1663,1791,1919,2047,2175,
							2303,2431,2559,2687,2815,2943,3071,3199,3327,3455,3583,3711,3839,3967,4095};

u16  AnyWaveTab[32] = {0};	  //存储任意的波形数据
/*-------------------------------------
 函数功能: DAC参数配置,默认产生正弦波
 函数参数: 无
 返 回 值: 无
-------------------------------------*/
void DAC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	DMA_InitTypeDef  DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	//DAC1->PA4   DAC2->PA5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//设置为模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);   //PA4 = 1
		
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	
	DACTriggerByTIM2(800,0);		  //2812Hz正弦波
	
	DMA_DeInit(DMA2_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x40007408; //DAC_DHR12R1_Address
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SineWaveTab;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 32;				   //波形点数32
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
/*--------------------------
 函数功能: DAC输出直流电压设置
 函数参数: 电压值vol
 返 回 值: 无
--------------------------*/
void Set_DAC_Value(unsigned int vol)	//vod:0~3300 = 0~3.3V
{
	float temp;
	temp = vol;
	temp /= 1000;
	temp = temp*(4095/3.3);
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);
}
/*-----------------------------------------------
函数功能: TIM2定时器配置模块
函数参数: ARR寄存器值0-65535,预分频值0-65535
调用示例: DACTriggerByTIM2(1,1);
-----------------------------------------------*/
void DACTriggerByTIM2(unsigned short int Auto_Reload,unsigned short int Clock_Div)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler =  Clock_Div; 			//时钟预分频
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_Period = Auto_Reload;				//自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	    //时钟分频1
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);       //使用TIM2事件更新作为DAC触发
	TIM_Cmd(TIM2,ENABLE);    //打开TIM2
}
