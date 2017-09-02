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
#ifndef __OSCILLOSCOPE_H__
#define __OSCILLOSCOPE_H__

/*--------------------------------------------------------
			波形配置数据结构,存储了波形配置参数
--------------------------------------------------------*/
typedef struct
{
    unsigned char SavedSD;
	unsigned char ReadSD;
	unsigned char UpdatTrue;
    unsigned char Stop;
    unsigned char TriggerMode;
	unsigned char Gain;
	unsigned int  TimeBase;	
    float AmpDiv;
    float TimDiv;
}WaveMode;
/*--------------------------------------------------------
			波形数据结构,存储了波形的常用参数
--------------------------------------------------------*/
typedef struct
{
    volatile unsigned int HighWidth;
    volatile unsigned int LowWidth;
    volatile float Vmax;
    volatile float Vmin;
	volatile float Vpp;
	volatile float Vrms;
    volatile unsigned int Priod;
    volatile unsigned int DutyCycle;
    volatile unsigned int Frequency;
}WaveType;
/*--------------------------------------------------------
			信号发生器波形数据结构
--------------------------------------------------------*/
typedef struct
{
	volatile float Vpp;
    volatile unsigned char DutyCycle;
    volatile unsigned int Frequency;
}FG_WaveType;
/*--------------------------------------------------------
				  函数发生器枚举类型
--------------------------------------------------------*/
typedef enum
{ 
  Sine_Wave = 1,
  Triangle_Wave, 
  Rectangular_Wave,
  Square_Wave,
  Sawtooth_Wave,
  Noise_Wave
}FunctionGeneratorType;
/*--------------------------------------------------------
					增益控制排列组合
--------------------------------------------------------*/
#define GAINX0_05	WaveCtrl.AmpDiv=9.39;JDQ_AV=1;CD4051C=1;CD4051B=0;CD4051A=1
#define GAINX0_1	WaveCtrl.AmpDiv=5.00;JDQ_AV=1;CD4051C=1;CD4051B=1;CD4051A=0
#define GAINX1		WaveCtrl.AmpDiv=1.00;JDQ_AV=0;CD4051C=1;CD4051B=1;CD4051A=1
#define GAINX2		WaveCtrl.AmpDiv=0.52;JDQ_AV=0;CD4051C=1;CD4051B=0;CD4051A=0
#define GAINX4		WaveCtrl.AmpDiv=0.25;JDQ_AV=0;CD4051C=1;CD4051B=0;CD4051A=0
#define GAINX5		WaveCtrl.AmpDiv=0.20;JDQ_AV=0;CD4051C=0;CD4051B=1;CD4051A=0
#define GAINX10		WaveCtrl.AmpDiv=0.10;JDQ_AV=0;CD4051C=0;CD4051B=0;CD4051A=1
#define GAINX25		WaveCtrl.AmpDiv=0.04;JDQ_AV=0;CD4051C=0;CD4051B=0;CD4051A=0


float AutoGainScan(void);
void ManualGainScan(unsigned int gain);
unsigned int GetSquareWavePriod(void);
unsigned int GetSquareWaveDutyCycles(void);
void FunctionGenerator(FunctionGeneratorType ft,unsigned int feq,float amp,unsigned char duty);
void TimeBaseControl(unsigned short int TimeBASE);
void FG_StartOutput(unsigned short int WaveTab[]);

#endif
