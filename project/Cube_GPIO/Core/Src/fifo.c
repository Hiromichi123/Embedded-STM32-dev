#include "fifo.h"

__IO FIFO_t rxFIFO = {0};

//��ʼ������
void initQueue(void)
{
	rxFIFO.ptrRead  = 0;
	rxFIFO.ptrWrite = 0;
}

//���
void fifo_enQueue(uint16_t data)
{
	rxFIFO.buffer[rxFIFO.ptrWrite] = data;
	
	++rxFIFO.ptrWrite;
	
	if(rxFIFO.ptrWrite >= FIFO_SIZE)
	{
		rxFIFO.ptrWrite = 0;
	}
}

//����
uint16_t fifo_deQueue(void)
{
	uint16_t element = 0;

	element = rxFIFO.buffer[rxFIFO.ptrRead];

	++rxFIFO.ptrRead;

	if(rxFIFO.ptrRead >= FIFO_SIZE)
	{
		rxFIFO.ptrRead = 0;
	}

	return element;
}

//�жϿն���
bool fifo_isEmpty(void)
{
	if(rxFIFO.ptrRead == rxFIFO.ptrWrite)
	{
		return true;
	}

	return false;
}

//������г���
uint16_t fifo_queueLength(void)
{
	if(rxFIFO.ptrRead <= rxFIFO.ptrWrite)
	{
		return (rxFIFO.ptrWrite - rxFIFO.ptrRead);
	}
	else
	{
		return (FIFO_SIZE - rxFIFO.ptrRead + rxFIFO.ptrWrite);
	}
}