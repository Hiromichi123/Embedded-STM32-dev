#include "uart_com.h"
#include "string.h"
#include "stdlib.h"


UARTCOM_Typedef uart6_com;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
	if(huart == &huart6 && uart6_com.rxUpdateFlag == 0)
	{
		if(uart6_com.Uart_Rx_Cnt >= 255)
		{
			uart6_com.Uart_Rx_Cnt = 0;
			memset(uart6_com.Uart_RxBuff,0x00,sizeof(uart6_com.Uart_RxBuff));
		}
		else
		{
			if(uart6_com.aRxBuffer == '@')
			{
				uart6_com.startReadFlag = 1;
			}
			if(uart6_com.startReadFlag == 1)
			{
				uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)++] = uart6_com.aRxBuffer;
				if((uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)-1] == 0x0A)&&(uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)-2] == 0x0D))
				{
					uart6_com.startReadFlag = 0;
					for(int i = FIFO_DEPTH-1; i > 0; i--)
					{
						strcpy((char*)uart6_com.RxFIFO[i], (char*)uart6_com.RxFIFO[i-1]);
					}
					strcpy((char*)uart6_com.RxFIFO[0], (char*)uart6_com.Uart_RxBuff);
					UARTCOM_Reset(&uart6_com);
				}
			}
		}
	}
	HAL_UART_Receive_IT(&huart6, (uint8_t *)&(uart6_com.aRxBuffer), 1);
	
	
//	if(huart == &huart6 && uart6_com.rxUpdateFlag == 0)
//	{
//		if(uart6_com.Uart_Rx_Cnt >= 255)
//		{
//			uart6_com.Uart_Rx_Cnt = 0;
//			memset(uart6_com.Uart_RxBuff,0x00,sizeof(uart6_com.Uart_RxBuff));
//		}
//		else
//		{
//			if(uart6_com.aRxBuffer == '@')
//			{
//				uart6_com.startReadFlag = 1;
//			}
//			if(uart6_com.startReadFlag == 1)
//			{
//				uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)++] = uart6_com.aRxBuffer;
//				if((uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)-1] == 0x0A)&&(uart6_com.Uart_RxBuff[(uart6_com.Uart_Rx_Cnt)-2] == 0x0D))
//				{
//					uart6_com.startReadFlag = 0;
//					uart6_com.rxUpdateFlag = 1;
//				}
//			}
//		}
//	}
//	HAL_UART_Receive_IT(&huart6, (uint8_t *)&(uart6_com.aRxBuffer), 1);
}



void Get_Data(const char* str, char* dst, char start, char end)
{
	int i = 0, j = 0;
	while(str[i++] != start && i <= 15);
	while(str[i] != end && j <= 15)
	{
		dst[j++] = str[i++];
	}
	dst[j] = '\0';
}

void UARTCOM_Reset(UARTCOM_Typedef* uartcom)
{
	memset(uartcom->Uart_RxBuff, 0x00, sizeof(uartcom->Uart_RxBuff));
	uartcom->Uart_Rx_Cnt = 0;
}

void UARTCOM_Get2Data(UARTCOM_Typedef* uartcom)
{
	char *ptr;
	ptr = strchr((char*)uart6_com.RxFIFO[FIFO_DEPTH-1], 'a');
	if(ptr != NULL)
	{
		uart6_com.data[0] = atoi(ptr+1);
	}
	ptr = strchr((char*)uart6_com.RxFIFO[FIFO_DEPTH-1], 'b');
	if(ptr != NULL)
	{
		uart6_com.data[1] = atoi(ptr+1);
	}
}

int get_mode(const char* str)
{
	char p[10];
	Get_Data(str,p,'a','b');
	int a;
	a = atoi(p);
	return a;
}
int get_number(const char* str)
{
	char p[10];
	Get_Data(str,p,'b','c');
	int a;
	a = atoi(p);
	return a;
}
