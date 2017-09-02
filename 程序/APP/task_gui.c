/*-------------------------------------------------------------------------------------------
 			                   STM32示波器GUI任务
 
 说明: 示波器需要良好的人机界面交互才具备可操作性,本GUI任务完成液晶屏和触摸屏的人机界面交互
	   采用了uCGUI-MEMDEV技术来完成波形显示窗口无闪烁绘制图形,其余GUI均为自写的GUI.
	   包括追踪线的计算,显示;无闪烁绘制波形算法,显示参数面板,显示交互菜单,检测事件发生等等
	   最核心的函数为处理AD缓冲区的数据,完成了寻找最大值最小值等等电参量的计算.浮点运算较多.
	   为保证对共享资源的有效和安全利用,采用了互斥信号量进行操作,保证共享资源安全.

 版本: v1.0 2013/11/30 	最初原始版本  
 	   v3.0 2014/2/18   基本完成版本    
  
 BoX编写   
-------------------------------------------------------------------------------------------*/
#include "task_gui.h"
#include "tft_api.h"

#include "GUI.h"
#include "LCDConf.h"
#include "math.h"
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
#include "oscilloscope.h"

/*------------------------------------------
		    追踪线宏定义
------------------------------------------*/
#define TRACKLINE_BOTH_CLOSE 	(0)
#define TRACKLINE_VPP_OPEN   	(1)
#define TRACKLINE_PRIOD_OPEN 	(2)
#define TRACKLINE_BOTH_OPEN  	(3)

#define PRAMPANEL_BOTH_CLOSE 	(0)
#define PRAMPANEL_TIME_OPEN   	(1)
#define PRAMPANEL_VOLT_OPEN 	(2)
#define PRAMPANEL_BOTH_OPEN  	(3)

/*------------------------------------------
		    	声明变量
------------------------------------------*/
extern  OS_EVENT *LCD_Buffer_MUTEX;
extern  OS_EVENT *USART_Buffer_MUTEX;
extern  OS_EVENT *SDtoRAM_Buffer_MUTEX;

extern  u8  LCD_Buffer[LCD_BUFFER_SIZE];
extern  u8  USART_Buffer[USART_BUFFER_SIZE];
extern  u16 ADCConvertedValue[SAMPDEPTH];

extern  WaveType    WaveInfo;			  //波形参数
extern  WaveMode    WaveCtrl;			  //控制参数
extern  FG_WaveType FG_WaveInfo;	      //信号发生器参数

INT16S  ADCVlaue2ScreenValue[SAMPDEPTH];  //显示波形缓冲区,占用RAM 0.78KB

u8      TrackLine_VppMax,				  //追踪线全局变量
		TrackLine_VppMin;

u16		TrackLine_PriodStart,
		TrackLine_PriodEnd;
										  
u8      TrackLine_Switch = TRACKLINE_BOTH_CLOSE; //追踪线开关
u8      PramPanel_Switch = PRAMPANEL_BOTH_CLOSE; //参数面板开关

u16 	Tpx=0,Tpy=0,ZBX=0,ZBY=0;		  //触摸屏AD值,坐标值

/*----------------------------------------------------------------
 函数功能: GUI_DrawGraph(I16 *paY, int NumPoints, int x0, int y0);
 函数参数: paY - 纵坐标的数组头指针
   		   NumPoints - 所需绘制的图象的点数
		   x0,y0 - 坐标原点在TFT_LCD屏幕上的坐标
 返 回 值: 无
-----------------------------------------------------------------*/
void Draw(void *p) 
{
	int i;
	(void)p;
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_LIGHTBLUE);
	GUI_SetFont(&GUI_Font6x8);
	GUI_SetTextMode(GUI_TM_TRANS); 			 //透明文本模式
	GUI_ClearRect(0,0,SAMPDEPTH,200);
	GUI_DrawRect (0,0,SAMPDEPTH-1,200);	  
	
	//画水平刻度线
	for (i = 0; i < 200; i += 20) 
	{
		GUI_DrawHLine(20 + i,1,SAMPDEPTH-1);  //(Y轴坐标,起点X坐标,终点X坐标)
	}
	GUI_DrawHLine(101,1,SAMPDEPTH-1);
	GUI_DrawHLine(99,1,SAMPDEPTH-1);
	//画垂直刻度线
	for (i = 40; i <= SAMPDEPTH; i += 40) 
	{
		GUI_DrawVLine(0 + i,1,200);
	}
	GUI_DrawVLine(199,1,200);
	GUI_DrawVLine(201,1,200);
	//画标度尺
	for (i = 10; i < 200;i += 20)GUI_DrawHLine(i,195,205);
	for (i = 20; i < 400;i += 40)GUI_DrawVLine(i,95,105);
	//画追踪线
	if(TrackLine_Switch != TRACKLINE_BOTH_CLOSE)
	{   
		GUI_SetColor(GUI_GREEN);
		switch(TrackLine_Switch)
		{
		 	case TRACKLINE_VPP_OPEN:
				 GUI_DrawHLine(TrackLine_VppMax+4,1,SAMPDEPTH-2);
				 GUI_DrawHLine(TrackLine_VppMin,1,SAMPDEPTH-2);
				 GUI_DispDecAt(TrackLine_VppMax,2,TrackLine_VppMax+6,3);
				 GUI_DispDecAt(TrackLine_VppMin,2,TrackLine_VppMin-8,3);
				 break;
			
			case TRACKLINE_PRIOD_OPEN:	
				 GUI_DrawVLine(TrackLine_PriodStart-2,1,187);
				 GUI_DrawVLine(TrackLine_PriodEnd+2,1,187);
				 GUI_DispDecAt(TrackLine_PriodEnd,TrackLine_PriodEnd-6,190,3);
				 GUI_DispDecAt(TrackLine_PriodStart,TrackLine_PriodStart-9,190,3);
				 break;

			case TRACKLINE_BOTH_OPEN:
				 GUI_DrawHLine(TrackLine_VppMax+4,1,SAMPDEPTH-2);
				 GUI_DrawHLine(TrackLine_VppMin,1,SAMPDEPTH-2);
				 GUI_DispDecAt(TrackLine_VppMax,2,TrackLine_VppMax+6,3);
				 GUI_DispDecAt(TrackLine_VppMin,2,TrackLine_VppMin-8,3);
				 
				 GUI_DrawVLine(TrackLine_PriodStart-2,1,187);
				 GUI_DrawVLine(TrackLine_PriodEnd+2,1,187);
				 GUI_DispDecAt(TrackLine_PriodEnd,TrackLine_PriodEnd-6,190,3);
				 GUI_DispDecAt(TrackLine_PriodStart,TrackLine_PriodStart-9,190,3);
			     break;
			default:break;	
		}
	}

	GUI_SetColor(GUI_YELLOW);
	GUI_DrawGraph(ADCVlaue2ScreenValue,SAMPDEPTH,0,0);//往GUI中绘波形图
//	GUI_DispDecAt(ZBX,370,25,3);
//	GUI_DispDecAt(ZBY,370,45,3);
	
	if(PramPanel_Switch != PRAMPANEL_BOTH_CLOSE)
	{		
		switch(PramPanel_Switch)
		{
			case PRAMPANEL_VOLT_OPEN:
				 GUI_DispStringAt("Vmax = ",320,120);GUI_DispFloat(WaveInfo.Vmax,5);
				 GUI_DispStringAt("Vmin = ",320,130);GUI_DispFloat(WaveInfo.Vmin,5);
				 GUI_DispStringAt("Vpp  = ",320,140);GUI_DispFloat(WaveInfo.Vpp,5);
				 GUI_DispStringAt("Vrms = ",320,150);GUI_DispFloat(WaveInfo.Vrms,5);
				 break;

			case PRAMPANEL_TIME_OPEN:
				 GUI_DispStringAt("Priod= ",220,120);GUI_DispDecMin(WaveInfo.Priod);GUI_DispString("uS");
				 GUI_DispStringAt("Freq = ",220,130);GUI_DispDecMin(WaveInfo.Frequency);GUI_DispString("Hz");
				 GUI_DispStringAt("High = ",220,140);GUI_DispDecMin(WaveInfo.HighWidth);GUI_DispString("uS");
				 GUI_DispStringAt("Lows = ",220,150);GUI_DispDecMin(WaveInfo.LowWidth);GUI_DispString("uS");
				 GUI_DispStringAt("Duty = ",220,160);GUI_DispDecMin(WaveInfo.DutyCycle);GUI_DispString("%");
				 break;

			case PRAMPANEL_BOTH_OPEN:
				 GUI_DispStringAt("Vmax = ",320,120);GUI_DispFloat(WaveInfo.Vmax,5);
				 GUI_DispStringAt("Vmin = ",320,130);GUI_DispFloat(WaveInfo.Vmin,5);
				 GUI_DispStringAt("Vpp  = ",320,140);GUI_DispFloat(WaveInfo.Vpp,5);
				 GUI_DispStringAt("Vrms = ",320,150);GUI_DispFloat(WaveInfo.Vrms,5);
				 GUI_DispStringAt("Priod= ",220,120);GUI_DispDecMin(WaveInfo.Priod);GUI_DispString("uS");
				 GUI_DispStringAt("Freq = ",220,130);GUI_DispDecMin(WaveInfo.Frequency);GUI_DispString("Hz");
				 GUI_DispStringAt("High = ",220,140);GUI_DispDecMin(WaveInfo.HighWidth);GUI_DispString("uS");
				 GUI_DispStringAt("Lows = ",220,150);GUI_DispDecMin(WaveInfo.LowWidth);GUI_DispString("uS");
				 GUI_DispStringAt("Duty = ",220,160);GUI_DispDecMin(WaveInfo.DutyCycle);GUI_DispString("%");
				 break;

			default:break;
		}
	}
}
/*-----------------------------------------
 函数功能:在LCD上显示波形关键参数
 函数说明:注意本函数多次操作共享资源,使用了
		  互斥信号量作为安全保证
------------------------------------------*/
void DisplayWaveInfo(void)
{
	uint8_t err;
 	//完成电压参数显示
	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量		
	sprintf(LCD_Buffer,"Vmax:%1.2fV  Vmin:%1.2fV  Vpp:%2.2fV  Vrms:%2.2fV",WaveInfo.Vmax,
												       			   		   WaveInfo.Vmin,
												       			   		   WaveInfo.Vpp,
																   		   WaveInfo.Vrms);
	LCD_Write_String(10,210,LCD_Buffer,Green,Black);	
	OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量

	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
	sprintf(LCD_Buffer,"T:%5duS   F:%5dHz ",WaveInfo.Priod,WaveInfo.Frequency);
	LCD_Write_String(10,230,LCD_Buffer,Green,Black);
	OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量

	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
	sprintf(LCD_Buffer,"H:%5duS   L:%5duS    Duty:%2d ",WaveInfo.HighWidth,
												        WaveInfo.LowWidth,
												        WaveInfo.DutyCycle);
	LCD_Write_String(10,250,LCD_Buffer,Green,Black);
	OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量

//	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
//	sprintf(LCD_Buffer,"AMP:%.2f",WaveCtrl.AmpDiv);												      
//	LCD_Write_String(210,225,LCD_Buffer,Green,Black);
//	OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量
	
	OSMutexPend(LCD_Buffer_MUTEX,0,&err);	   //占用信号量
	sprintf(LCD_Buffer,"TMP:%d ",GetTempSensor());												      
	LCD_Write_String(210,230,LCD_Buffer,Green,Black);
	OSMutexPost(LCD_Buffer_MUTEX);			   //释放信号量
}
/*-----------------------------------------
 函数说明:在LCD上显示实时波形
------------------------------------------*/
void ShowRealTimeWave(void)
{
	GUI_RECT Rect = {0,0,479,200};					 //无闪烁显示区域
	int i,j=0;
	OS_CPU_SR  cpu_sr = 0u;
	WaveInfo.Vmax = 2047.0;
	WaveInfo.Vmin = 2047.0;

	for (i = 0; i < SAMPDEPTH; i++) 
	{	//把AD值按比例转换成在LCD上显示的值
		ADCVlaue2ScreenValue[i] = ( ADCConvertedValue[i]*200/4096 );  
			
		if(WaveInfo.Vmax < ADCConvertedValue[i])	 //找出Vmax Vmin
		{
			WaveInfo.Vmax = ADCConvertedValue[i];	
		}
		if(WaveInfo.Vmin > ADCConvertedValue[i])
		{
		 	WaveInfo.Vmin = ADCConvertedValue[i];	
		}
		//周期追踪线寻找
		if(ADCVlaue2ScreenValue[i]>98 && ADCVlaue2ScreenValue[i]<102 && j==0 && i>10 && i<200)
		{
			if(ADCVlaue2ScreenValue[i-5]>101 && ADCVlaue2ScreenValue[i+5]<99)
			{
		 		TrackLine_PriodStart = i;
				j = 1;
			}
		}
		else if(ADCVlaue2ScreenValue[i]>98 && ADCVlaue2ScreenValue[i]<102 && j==1 && i>TrackLine_PriodStart+20 && i<SAMPDEPTH)
		{
			if(ADCVlaue2ScreenValue[i-5]>101 && ADCVlaue2ScreenValue[i+5]<99)
			{
		 		TrackLine_PriodEnd = i;
				j = 2;
			}
		}
	}
	
	TrackLine_VppMax = 200 - WaveInfo.Vmax*200/4096;	 //最大值追踪线
	TrackLine_VppMin = 200 - WaveInfo.Vmin*200/4096;	 //最小值追踪线
	
	if(JDQ_ACDC == 1)   //AC耦合
	{
	 	WaveInfo.Vmax -= 2047.0;
		WaveInfo.Vmin -= 2047.0;	
	}
	WaveInfo.Vmax = (WaveInfo.Vmax/4095 * 3.3 * WaveCtrl.AmpDiv);
	WaveInfo.Vmin = (WaveInfo.Vmin/4095 * 3.3 * WaveCtrl.AmpDiv);
	WaveInfo.Vpp  = WaveInfo.Vmax - WaveInfo.Vmin;	
	WaveInfo.Vrms = WaveInfo.Vpp*1000 / 2828;	
	
	OS_ENTER_CRITICAL();
	GUI_MEMDEV_Draw(&Rect,&Draw,ADCVlaue2ScreenValue,0,0); //GUI无闪烁绘制波形
	OS_EXIT_CRITICAL();	
}

/*-----------------------------------------
 函数说明:在LCD上显示存储的波形
------------------------------------------*/
void ShowSavedWave(void)
{
	uint16_t i;
//	SD_LoadWaveADValue();		  //从SD卡载入波形
	WaveCtrl.ReadSD = 0;
	WaveInfo.Vmax = 2047.0;
	WaveInfo.Vmin = 2047.0;
	LCD_Clear_Select(2,2,478,200,Black);
	for(i=3; i<SAMPDEPTH-2; i++)
	{	
		Draw_Line(i-1,(uint16_t)((ADCConvertedValue[i-1]*200/4096)),
				  i,  (uint16_t)((ADCConvertedValue[i]*200/4096)),Blue2);
		Draw_Line(i-1,(uint16_t)((ADCConvertedValue[i-1]*200/4096)+1),
				  i,  (uint16_t)((ADCConvertedValue[i]*200/4096)+1),Blue2);		
		if(WaveInfo.Vmax < (float)ADCConvertedValue[i])
		{
			WaveInfo.Vmax =(float)ADCConvertedValue[i];	
		}
		if(WaveInfo.Vmin > (float)ADCConvertedValue[i])
		{
		 	WaveInfo.Vmin =(float)ADCConvertedValue[i];	
		}
	}	 
	
	if(JDQ_ACDC == 1)   //AC耦合
	{
	 	WaveInfo.Vmax -= 2047.0;
		WaveInfo.Vmin -= 2047.0;	
	}
	WaveInfo.Vmax = (float)(WaveInfo.Vmax/4095 * 3.3 * WaveCtrl.AmpDiv);
	WaveInfo.Vmin = (float)(WaveInfo.Vmin/4095 * 3.3 * WaveCtrl.AmpDiv);
	WaveInfo.Vpp = WaveInfo.Vmax - WaveInfo.Vmin;	
	WaveInfo.Vrms = WaveInfo.Vpp*1000 / 2828;	
}

void ShowWelcomeScreen(void)
{
	Draw_Rectangle(132,70,132*2,90*2,Blue2);
	Draw_Rectangle(131,69,132*2-1,90*2-1,Blue2);		
	LCD_Write_String(132+4,70+6," ARM  Cortex-M3",Yellow,Black);
	LCD_Write_String(132+11,70+36,"    Digital",Yellow,Black);
	LCD_Write_String(132+13,70+64," Oscilloscope",Yellow,Black);
	LCD_Write_String(132+13,70+84,"BoX 2013-11-23",Yellow,Black);
}
/*-----------------------------------------
 函数说明:在LCD上显示控制面板
------------------------------------------*/
void DrawControlPanel(void)
{
 	GUI_DrawRect(403,1,477,20);		 //侧边菜单
	GUI_DrawRect(404,2,476,19);

	GUI_DrawRect(1,202,400,270);	 //参数栏
	GUI_DrawRect(2,203,399,269);
	
	GUI_SetFont(&GUI_Font8x16);
	GUI_DispStringHCenterAt("BoX",440,3);
	
	GUI_DrawRect(403,23,477,63);	 //STOP,RUN
	GUI_DrawRect(404,24,476,62);
	GUI_DrawVLine(440,23,63);
	GUI_DrawVLine(441,23,63);
	GUI_DispStringAt("STOP",407,38);
	GUI_DispStringAt("RUN",447,38);

	GUI_DrawRect(403,65,477,105);	 //AC,DC 
	GUI_DrawRect(404,66,476,104);
	GUI_DrawVLine(440,65,105);
	GUI_DrawVLine(441,65,105);
	GUI_DispStringAt("AC",415,78);
	GUI_DispStringAt("DC",450,78);

	GUI_DrawRect(403,108,477,148);	  //X+ X-
	GUI_DrawRect(404,109,476,147);
	GUI_DrawVLine(440,108,148);
	GUI_DrawVLine(441,108,148);
	GUI_DispStringAt("X+",415,121);
	GUI_DispStringAt("X-",450,121);

	GUI_DrawRect(403,150,477,190);	  //Y+ Y-
	GUI_DrawRect(404,151,476,189);
	GUI_DrawVLine(440,150,190);
	GUI_DrawVLine(441,150,190);
	GUI_DispStringAt("Y+",415,163);
	GUI_DispStringAt("Y-",450,163);

	GUI_DrawRect(403,192,477,230);	  //FG
	GUI_DrawRect(404,193,476,229);
	GUI_DrawVLine(440,192,230);
	GUI_DrawVLine(441,192,230);
	GUI_DispStringAt("SIN",410,205);
	GUI_DispStringAt("SQU",447,205);

	GUI_DrawRect(403,232,477,271);	  //FG
	GUI_DrawRect(404,231,476,270);
	GUI_DrawVLine(440,232,271);
	GUI_DrawVLine(441,232,271);
	GUI_DispStringAt("AUTO",407,245);
	GUI_DispStringAt("TRG",447,245);
}
/*-----------------------------------------
 函数说明:在LCD上显示参数面板
------------------------------------------*/
void DrawPramPanel(void)
{

}
/*-----------------------------------------
 函数说明:触摸事件检测,根据触摸坐标检测哪个
 		  被按下,判断值由实验法测定
------------------------------------------*/
void TouchEventDetected(void)
{
	if(ZBX>421 && ZBX<440 && ZBY>58 && ZBY<86)  //STOP
	{
		Draw_Rectangle(441,23,477,63,White);	//反白RUN 
		Draw_Rectangle(442,24,476,62,White);		
		LCD_Write_String(447,38,"RUN",White,Black);

		Draw_Rectangle(403,23,440,63,Magenta);	//改色STOP 
		Draw_Rectangle(404,24,439,62,Magenta);		
		LCD_Write_String(407,38,"STOP",Magenta,Black);
		
		WaveCtrl.Stop = 1;
	}
	if(ZBX>449 && ZBX<475 && ZBY>58 && ZBY<86)  //RUN
	{
		Draw_Rectangle(403,23,440,63,White);	//同上…… 
		Draw_Rectangle(404,24,439,62,White);		
		LCD_Write_String(407,38,"STOP",White,Black);

		Draw_Rectangle(441,23,477,63,Magenta);	 
		Draw_Rectangle(442,24,476,62,Magenta);		
		LCD_Write_String(447,38,"RUN",Magenta,Black);
	 	
		WaveCtrl.Stop = 0;
	} 
	if(ZBX>421 && ZBX<440 && ZBY>98 && ZBY<121)  //AC
	{
		Draw_Rectangle(441,65,477,105,White);	 
		Draw_Rectangle(442,66,476,104,White);		
		LCD_Write_String(450,78,"DC",White,Black);
		
		Draw_Rectangle(403,65,440,105,Magenta);	 
		Draw_Rectangle(404,66,439,104,Magenta);		
		LCD_Write_String(415,78,"AC",Magenta,Black);
		
		JDQ_ACDC = 1;
	}
	if(ZBX>449 && ZBX<475 && ZBY>98 && ZBY<121)  //DC
	{
		Draw_Rectangle(403,65,440,105,White);	 
		Draw_Rectangle(404,66,439,104,White);		
		LCD_Write_String(415,78,"AC",White,Black);

		Draw_Rectangle(441,65,477,105,Magenta);	 
		Draw_Rectangle(442,66,476,104,Magenta);		
		LCD_Write_String(450,78,"DC",Magenta,Black);
	 	
		JDQ_ACDC = 0;
	} 
	if(ZBX>421 && ZBX<440 && ZBY>131 && ZBY<159)  //X+
	{
	 	WaveCtrl.TimeBase += 5;
		if(WaveCtrl.TimeBase >= 1000)
			WaveCtrl.TimeBase = 1000;
		TimeBaseControl(WaveCtrl.TimeBase);
	}
	if(ZBX>449 && ZBX<475 && ZBY>131 && ZBY<159)  //X-
	{
	 	WaveCtrl.TimeBase -= 5;									  
		if(WaveCtrl.TimeBase <= 1)
			WaveCtrl.TimeBase = 1;
		TimeBaseControl(WaveCtrl.TimeBase);
	} 
	if(ZBX>421 && ZBX<440 && ZBY>167 && ZBY<194)  //Y+
	{
		if(++WaveCtrl.Gain > 8)
	   		WaveCtrl.Gain = 1;
		ManualGainScan(WaveCtrl.Gain);
	}
	if(ZBX>449 && ZBX<475 && ZBY>167 && ZBY<194)  //Y-
	{
		if(--WaveCtrl.Gain < 1)
	   		WaveCtrl.Gain = 8;
		ManualGainScan(WaveCtrl.Gain);
	}
	if(ZBX>421 && ZBX<440 && ZBY>203 && ZBY<229)  //SIN
	{
		Draw_Rectangle(441,232,477,271,White);	 
		Draw_Rectangle(442,231,476,270,White);		
		LCD_Write_String(447,245,"TRG",White,Black);

		Draw_Rectangle(441,192,477,230,White);	 
		Draw_Rectangle(442,193,476,229,White);		
		LCD_Write_String(447,205,"SQU",White,Black);
		
		Draw_Rectangle(403,192,440,230,Magenta);	 
		Draw_Rectangle(404,193,439,229,Magenta);		
		LCD_Write_String(410,205,"SIN",Magenta,Black);
//		Program Size: Code=61216 RO-data=8280 RW-data=340 ZI-data=30100
//		Program Size: Code=55724 RO-data=8268 RW-data=256 ZI-data=29912
//      Program Size: Code=55688 RO-data=6456 RW-data=256 ZI-data=25160      
	 	FunctionGenerator(Sine_Wave,3000,2.5,50);	
	}
	if(ZBX>449 && ZBX<475 && ZBY>203 && ZBY<229)  //SQU
	{
		Draw_Rectangle(441,232,477,271,White);	 
		Draw_Rectangle(442,231,476,270,White);		
		LCD_Write_String(447,245,"TRG",White,Black);

		Draw_Rectangle(403,192,440,230,White);	 
		Draw_Rectangle(404,193,439,229,White);		
		LCD_Write_String(410,205,"SIN",White,Black);

		Draw_Rectangle(441,192,477,230,Magenta);	 
		Draw_Rectangle(442,193,476,229,Magenta);		
		LCD_Write_String(447,205,"SQU",Magenta,Black);
	 	
		FunctionGenerator(Square_Wave,3000,2.5,50);
	} 
	if(ZBX>421 && ZBX<440 && ZBY>239 && ZBY<265)  //AUTO
	{	
		if(++TrackLine_Switch >	TRACKLINE_BOTH_OPEN)
			TrackLine_Switch = TRACKLINE_BOTH_CLOSE;	
		
		if(TrackLine_Switch == TRACKLINE_BOTH_CLOSE)
		{
			Draw_Rectangle(403,232,440,271,White);	 
			Draw_Rectangle(404,231,439,270,White);		
			LCD_Write_String(407,245,"AUTO",White,Black);			
		}
		else
		{
		 	Draw_Rectangle(403,232,440,271,Magenta);	 
			Draw_Rectangle(404,231,439,270,Magenta);		
			LCD_Write_String(407,245,"AUTO",Magenta,Black);
		}
	}
	if(ZBX>449 && ZBX<475 && ZBY>239 && ZBY<265)  //TRG
	{
		Draw_Rectangle(403,192,440,230,White);	 
		Draw_Rectangle(404,193,439,229,White);		
		LCD_Write_String(410,205,"SIN",White,Black);

		Draw_Rectangle(441,192,477,230,White);	 
		Draw_Rectangle(442,193,476,229,White);		
		LCD_Write_String(447,205,"SQU",White,Black);

		Draw_Rectangle(441,232,477,271,Magenta);	 
		Draw_Rectangle(442,231,476,270,Magenta);		
		LCD_Write_String(447,245,"TRG",Magenta,Black);

	 	FunctionGenerator(Triangle_Wave,3000,2.5,50);
	}
	if(ZBX>10 && ZBX<380 && ZBY>220 && ZBY<265)  //PRAM
	{
		if(PramPanel_Switch++ >	PRAMPANEL_BOTH_OPEN)
			PramPanel_Switch = PRAMPANEL_BOTH_CLOSE;	
	}  	
}
