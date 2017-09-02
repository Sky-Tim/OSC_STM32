#ifndef __USART1_H
#define __USART1_H

#include <stdio.h>
#include <stdarg.h>

/*-----------------------------------------
		    	宏定义开关
------------------------------------------*/
#define USART_BUFFER_SIZE 16
#define USART1_DR_Base  0x40013804

void USART1_Config(void);
int fputc(int ch,FILE *f);
void USART1_printf(USART_TypeDef * USARTx, unsigned char *Data,...);
static char *itoa(int value, char *string, int radix);

#endif
