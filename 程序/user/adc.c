/*---------------------------------------------------------
		  ADC配置驱动程序
	说明: 示波器AD采样配置,经过初步测试,AD采样速率为1.286M
	      正弦波最大不失真测量频率300kHz
		  三角波最大不失真测量频率150kHz
		  矩形波最大不失真测量频率100kHz
	时间: 2013年11月19日
---------------------------------------------------------*/
#include "stm32f10x.h"
#include "adc.h"
#include "oscilloscope.h"
#include "ucos_ii.h"
#include "tft_api.h"
/*-----------------------------------------
		    	声明变量
------------------------------------------*/
extern WaveType WaveInfo;
extern WaveMode WaveCtrl;
volatile u16 ADCConvertedValue[SAMPDEPTH];//AD转换缓冲区,占用RAM 0.8KB

/*-----------------------------------------
		    	ADC1端口初始化
------------------------------------------*/
void ADC1_GPIO_Init(void)
{
	GPIO_InitTypeDef IO_Init;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC,ENABLE);
	//C1模拟输入
	IO_Init.GPIO_Pin = GPIO_Pin_1;
	IO_Init.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC,&IO_Init);
}

/* #define ADC1_DR_Address ((unsigned int)0x40012400+0x4c) */
/* unsigned short int ADC1_DMA_Value; */
/*--------------------------------------------------
 函数说明:配置ADC1完成AD采集,是本示波器最核心的部分.
 配置方案:ADC1由TIM3提供的触发事件进行触发AD转换,控
 		  制TIM3的速率就可以完成采样率的改变.同时采
		  用DMA完成数据传输,注入通道1完成内部温度传
		  感器AD采集. 
--------------------------------------------------*/
void ADC1_Mode_Config(void)
{
	//配置DMA
	DMA_InitTypeDef DMA_csh;
	ADC_InitTypeDef ADC_csh;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	DMA_DeInit(DMA1_Channel1);  					   //DMA复位,通道1
	DMA_csh.DMA_PeripheralBaseAddr = ADC1_DR_Address;  //ADC1地址
	DMA_csh.DMA_MemoryBaseAddr = (unsigned int)ADCConvertedValue;  //内存地址
	DMA_csh.DMA_DIR = DMA_DIR_PeripheralSRC;  
	DMA_csh.DMA_BufferSize = SAMPDEPTH;  			  		//缓冲大小为采样深度
	DMA_csh.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址固定
	DMA_csh.DMA_MemoryInc = DMA_MemoryInc_Enable; 			//内存地址自增
	DMA_csh.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  
	DMA_csh.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_csh.DMA_Mode = DMA_Mode_Circular;  					//循环传输
	DMA_csh.DMA_Priority = DMA_Priority_High;  				//DMA优先级高
	DMA_csh.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_csh);  						//写入DMA1配置参数
	DMA_Cmd(DMA1_Channel1,ENABLE);	   						//使能DMA1通道1
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);			//使能DMA CH1中断

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//配置TIM3工作在18MHz,为AD提供触发
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = 1;          
	TIM_TimeBaseStructure.TIM_Prescaler = 99; 	//工作在18M，每格最大值时，不至于溢出      
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update); //使用TIM3事件更新作为ADC触发
	
	//配置ADC
	ADC_csh.ADC_Mode = ADC_Mode_Independent;  		//独立ADC模式
    ADC_csh.ADC_ScanConvMode = DISABLE;   			//关闭扫描模式
	ADC_csh.ADC_ContinuousConvMode = DISABLE;  		//连续AD转换开启
	ADC_csh.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;  //由TIM3提供的触发事件进行触发AD转换
	ADC_csh.ADC_DataAlign = ADC_DataAlign_Right; 	//数据右对齐
	ADC_csh.ADC_NbrOfChannel = 1;  					//要转换的通道数目1
	ADC_Init(ADC1,&ADC_csh);   						//写入ADC1配置参数
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1,ADC_SampleTime_1Cycles5);//采样速率1M
	ADC_DMACmd(ADC1,ENABLE); 						//使能ADC1 DMA
	ADC_ExternalTrigConvCmd(ADC1,ENABLE);			//打开ADC1外部触发
	
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);	 //配置ADC1通道16为注入通道1
	ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_None);	 //软件触发注入通道的转换
	ADC_TempSensorVrefintCmd(ENABLE);											 //使能温度传感器

	ADC_Cmd(ADC1,ENABLE); 							//使能ADC1
	ADC_ResetCalibration(ADC1);	  					//复位校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));     //等待校准寄存器复位完成
	ADC_StartCalibration(ADC1);	  					//开始校准
	while(ADC_GetCalibrationStatus(ADC1)); 			//等待校准完成
	TIM_Cmd(TIM3,ENABLE);
}
/*-----------------------------------------
 函数说明:通过注入通道1转换内部温度传感器
 		  AD值,读取10次有效数据取平均返回 
------------------------------------------*/
u16 GetTempSensor(void)   
{ 
	u16 temp=0,i,k=0;
	for(i=0; i<10; )
	{
		ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);	//软件触发注入通道的转换
		k = (0x6EE - ADC_GetInjectedConversionValue(ADC1,ADC_InjectedChannel_1)) / 0x05 + 25;
		if(k>0 && k<100)
		{
			temp += k;
			i++;
		}
	}
	temp /= 10;
	return temp;	     
}
/*-----------------------------------------
 函数说明:ADC1初始化 
------------------------------------------*/
void ADC1_Init(void)
{
	ADC1_GPIO_Init();
	ADC1_Mode_Config();
}
/*-----------------------------------------
 函数说明:ADC传输DMA通道1中断服务程序
 		  DMA把AD值传输到缓冲区完成后关闭定
		  时器3(作为触发AD转换的定时器)同时
		  置更新完成标志位为1,开定时器3在应
		  用中开启. 
------------------------------------------*/
void DMA1_Channel1_IRQHandler()
{
      OSIntNesting++;  
      DMA_ClearFlag(DMA1_FLAG_TC1);	//清除DMA传输完成中断
      TIM_Cmd(TIM3,DISABLE);		//关闭TIM3
      WaveCtrl.UpdatTrue = 1;		//已经完成一次波形FIFO,可以批量读出数据
      OSIntExit();
}
/*-----------------------------------------
 函数说明:擦除AD缓冲区 
------------------------------------------*/
void Earse_AD_FIFO(void)
{
	uint32_t i;
 	for(i=0; i<SAMPDEPTH; i++)
	{
		ADCConvertedValue[i] = 0;
	}	
}
