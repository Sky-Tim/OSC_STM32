/*-------------------------------------------------------------------------------------------
 			                   TSC2046触摸屏控制器驱动程序
 说明: TSC2046驱动程序,配套STM32F103VET6控制器对应奋斗4.3寸屏幕的TSC2046管脚连接如下
 	   ADS7843、ADS7846、TSC2046、XPT2046、AK4182驱动芯片都可以使用本驱动,且管脚兼容
	   (16)DCLK --- PA5(SPI1_CLK)
	   (15)CS   --- PB7
	   (14)DIN  --- PA7(SPI1_MOSI)
	   (12)DOUT --- PA6(SPI1_MISO)
	   (11)PEN  --- PB6(IPU)
       
	   本驱动程序的使用方法
	   1).先配置好stm32f10x_spi.c  tsc2046.c文件和头文件,比例系数和校准模式在头文件中配置
	   2).接着调用TSC2046_Config()初始化控制器
	   3).if(PENDIRQ == 0)
		  {
			TP_Read(&Tpx,&Tpy);
			TP_ADtoZB(&Tpx,&Tpy,&X,&Y);	
			Draw_Point(X,Y,Green);			
		  }
		  else...

 版本: v1.0 2013/10/9 	最初原始版本,提供硬件驱动程序  
 	   v1.1 2013/10/13  增加触摸屏校正,提供API接口,测定比例系数  
  
 BoX编写   
-------------------------------------------------------------------------------------------*/
#include "TSC2046.h"
#include "delay.h"
#include "stm32f10x.h"
#include "tft_api.h"


/*------------------------------------------------
  函数功能:		TSC2046硬件配置 
------------------------------------------------*/
void TSC2046_Config(void)
{
	SPI_Config();
}	
/*----------------------------------------
 函数功能: STM32 SPI1参数配置
 函数参数: 无
 返 回 值: 无
----------------------------------------*/
void SPI_Config(void)	  //奋斗板还接了其他SPI外设所以要把无关的关掉
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);	//使能APB2外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//记住使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                       RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
						   RCC_APB2Periph_GPIOE , ENABLE);
	//A5->SCK  A6->MISO A7->MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   //SPI用复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//C4->CS  FLASH的片选
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//B7->CS  触摸的片选
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//A4->CS 以太网片选
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//B12->CS VS1003片选
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	//触摸检测引脚配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	        //PENIRQ上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//SPI1配置
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//2线全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;			//SPI主
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//数据格式8位
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;				//时钟极性低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;		    //时钟相位第1边沿触发
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_32; 
															//TSC2046 SPI通信速率不能大于SYSCLK/32
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//MSB在前
	SPI_InitStructure.SPI_CRCPolynomial = 7;				//CRC多项式校验
	SPI_Init(SPI1,&SPI_InitStructure);

	SPI_Cmd(SPI1,ENABLE);

	GPIO_SetBits(GPIOB,GPIO_Pin_12);//禁止VS1003片选
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	//禁止以太网片选
	GPIO_SetBits(GPIOC,GPIO_Pin_4); //禁止FLASH片选
}
/*----------------------------------------
 函数功能: 向SPI发送一字节数据
 函数参数: 要发送的数据dat
 返 回 值: 器件发回来的数据
----------------------------------------*/
uint8 SPI_WriteByte(uint8 dat)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, dat);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
/*----------------------------------------
 函数功能: SPI读取一个字节
 函数参数: 空
 返 回 值: 从器件发来的一字节数据
----------------------------------------*/
uint8 SPI_ReadByte(void)
{
	return(SPI_WriteByte(0x00));	//记住MOSI发送MISO立即也发送
}
/*------------------------------------------------
  函数功能:		SPI读取TSC2046的X AD值 
  函数返回值:	uint16 X电压值
------------------------------------------------*/
uint16 TP_ReadX(void)
{
	uint16 temp;
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);   //CS = 0
	Software_Delay(20);
	SPI_WriteByte(0x90);				//0x90是读取X坐标值命令
	Software_Delay(20);
	temp = SPI_ReadByte();				//接收12位AD值
	temp <<= 8;
	temp += SPI_ReadByte();				//接收余下的8位AD值
	Software_Delay(20);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);		//CS = 1;
	temp >>= 3;							//换算成12位数据
	return temp;
}
/*------------------------------------------------
  函数功能:		SPI读取TSC2046的Y AD值 
  函数返回值:	uint16 Y电压值
------------------------------------------------*/
uint16 TP_ReadY(void)
{
	uint16 temp;
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);   //CS = 0
	Software_Delay(20);
	SPI_WriteByte(0xD0);
	Software_Delay(20);
	temp = SPI_ReadByte();
	temp <<= 8;
	temp += SPI_ReadByte();
	Software_Delay(20);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);		//CS = 1;
	temp >>= 3;							//换算成12位数据
	return temp;
}
/*------------------------------------------------
  函数功能:		读取TSC2046的触摸AD值 
  函数返回值:	存入指针中
  函数接口:     指针tpx,指针tpy 
------------------------------------------------*/
void TP_Read(uint16 *tpx,uint16 *tpy)
{
	float tempx=0,tempy=0;
	uint16 TpBufferX[10];				//数据缓存
	uint16 TpBufferY[10];
	uint8  i=0;
	do								    //读取10次AD值
	{
		*tpx = TP_ReadX();
		*tpy = TP_ReadY();
		if(*tpx>100 && *tpx<4000 && *tpy>100 && *tpy<4000) //确保读取的数据有效
		{
			TpBufferX[i] = *tpx;
			TpBufferY[i] = *tpy;
			i++;	
		}
	}while(PENDIRQ==0 && i<10);

	BubbleSort(TpBufferX,10); 	//升序排列
	BubbleSort(TpBufferY,10);
	for(i=3;i<8;i++)
	{
		tempx += TpBufferX[i];	//取出中间值
		tempy += TpBufferY[i];
	}
	tempx /= 5;				//计算平均值
	tempy /= 5;
	*tpx = (uint16)tempx;
	*tpy = (uint16)tempy;
}
/*------------------------------------------------
  函数功能:		改进算法的冒泡排序 
  函数返回值:	无
  函数接口:     数组首地址a,数组长度n 
  编写日期:		2013年6月6日
------------------------------------------------*/
void BubbleSort(uint16 a[],uint8 n)  //改进算法的冒泡排序 
{
    uint16 i,j,t,flag=0;
    for(i=0;i<n;i++)
    {
        for(j=n-1;j>i;j--)
        {
            if(a[j-1]<a[j])	 //升序排列
            {
                t=a[j-1];
                a[j-1]=a[j];
                a[j]=t;
                flag=1;
            }
        }
        if(flag==0)
			break;
        else 
			flag=0;
    }
}
/*----------------------------------------
 函数功能: AD-->坐标值转换
 函数参数: 空
 返 回 值: 从器件发来的一字节数据
----------------------------------------*/
void TP_ADtoZB(uint16 *tpx,uint16 *tpy,uint16 *x,uint16 *y)
{
#ifdef CONSTMODE			   //常数模式,不需要调整比例系数
	*x = ((4096-*tpx)/FACX);   //比例系数,该值和具体的屏幕有关系,这两个值是实验得出的结果.
	*y = ((4096-*tpy)/FACY);   //不同屏幕有不同比例系数,根据不同屏幕进行调整
#endif

#ifdef ADJMODE				   //校准模式,手动调节比例系数
	*x = ((4096-*tpx)/Kx);	   //如果使用校准则这个值应该在7.9-8.1
	*y = ((4096-*tpy)/Ky);	   //如果使用校准则这个值应该在14.1左右
#endif	
}
/*----------------------------------------
 函数功能: 触摸屏校准得出比例系数
 函数参数: 空
 返 回 值: 改变全局变量Kx,Ky
----------------------------------------*/
#ifdef ADJMODE
void TouchScreenAdjust()
{
	uint8 i,AdjTimes=0;
	uint16 Ax,Ay,Bx,By;
	/* 当Kx,Ky的比例系数不在正常范围内则一直校准直到正常或者超过3次为止
	 * 当超过3次仍然失败的时候则比例系数采取默认值FACX,FACY
	 * 下边界值的确定是根据实验法测得的
	 */
	while(AdjTimes < 3)	           //尝试次数3次
	{
		AdjTimes++;
		LCD_Write_String(180,200,"Touch First Point   ",Yellow,Black);
		for(i=0; i<20; i++)		   //在左上角点A(20,20)显示十字
	    {							
			Draw_Point(20,10+i,Green);
			Draw_Point(10+i,20,Green);
	    }
		while(1)
		{
			if(PENDIRQ == 0)
			{
				Software_Delay(10000);           //延时去抖
				while(PENDIRQ == 0)
				{
					TP_Read(&Ax,&Ay);
					Software_Delay(10000000);    //延时去抖
				}
				break;
			}
		}
			
		LCD_Write_String(180,200,"Touch Seconed Point",Yellow,Black);
		for(i=0; i<20; i++)		   //在中心点B(240,136)显示十字
	    {							
			Draw_Point(240,126+i,Green);
			Draw_Point(230+i,136,Green);
	    }
		while(1)
		{
			if(PENDIRQ == 0)
			{
				Software_Delay(10000);           //延时去抖
				while(PENDIRQ == 0)
				{
					TP_Read(&Bx,&By);
					Software_Delay(10000000);   //延时去抖
				}
				break;
			}
		}
		
		Kx = Ax - Bx;			   //计算x方向差值
		Ky = Ay - By;			   //计算y方向差值
		Kx = Kx / (240-20);	       //计算出每个像素的比例系数  
		Ky = Ky / (136-20);	       //计算出每个像素的比例系数  

		if(Kx<7.85 || Kx>8.05 || Ky<14.00 || Ky>14.15)
		{
			LCD_Write_String(180,230,"Adjuest Failure!",Yellow,Black);
			LCD_Clear_Select(0,0,300,200,Black);
		}
		else
		{				  // 当Kx,Ky的比例系数不在正常范围内则一直校准直到正常为止
	       break;         // 边界值的确定是根据实验法测得的               	
		}
	}//End of while
	AdjuestFlag = 1;	  //校准标过志位置1
	if(AdjTimes >= 3)	  //当超过3次仍然失败的时候则比例系数采取默认值FACX,FACY
	{
		Kx = FACX;
		Ky = FACY;
		LCD_Write_String(180,230,"Out of times!   ",Yellow,Black);
	}
	else
	{
		LCD_Write_String(180,230,"Adjuest Success!",Yellow,Black);
	}
}//End of Fun
#endif
