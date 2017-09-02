#ifndef __TASK_MAIN_H__
#define __TASK_MAIN_H__

#include "oscilloscope.h"

#define Trigger_Rising  1
#define Trigger_Falling 0

void TaskStackChack(void);
void GetFrequence(void);
void GetWaveADCValue(void);
void WaveMode_Init(WaveMode* WaveCtrl);
void SendDataToPC(void);
unsigned char PCtoMCU_Decoding(unsigned char Revdata[],unsigned int *cmd,unsigned int *pram);
void MCUtoPC_Coding(unsigned char data[]);
void ReceiveDataFromPC(void);

#endif
