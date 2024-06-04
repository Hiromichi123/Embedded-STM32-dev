#ifndef __UART_COM_H__
#define __UART_COM_H__

#include "main.h"
#include "usart.h"

#define FIFO_DEPTH 3
#define RXBUF_SIZE 256

typedef struct __uartCom__
{
	uint8_t aRxBuffer;
	uint8_t Uart_RxBuff[RXBUF_SIZE];
	uint8_t Uart_Rx_Cnt;
	uint8_t Uart_RxFlag;
	uint8_t RxFIFO[FIFO_DEPTH][RXBUF_SIZE];
	int rxUpdateFlag;
	int startReadFlag;
	int data[3];
}UARTCOM_Typedef;

extern UARTCOM_Typedef uart6_com, uart1_com;

void UARTCOM_Reset(UARTCOM_Typedef* uartcom);
void UARTCOM_GetData(UARTCOM_Typedef* uartcom);

#endif
