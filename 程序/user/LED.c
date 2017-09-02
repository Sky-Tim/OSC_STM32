#include "LED.H"

void LED_GPIO_Config(void)
{
  GPIO_InitTypeDef IO_Init;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
  IO_Init.GPIO_Pin = GPIO_Pin_All;				    
  IO_Init.GPIO_Mode = GPIO_Mode_Out_PP;
  IO_Init.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_Init(GPIOE, &IO_Init);	  
}

