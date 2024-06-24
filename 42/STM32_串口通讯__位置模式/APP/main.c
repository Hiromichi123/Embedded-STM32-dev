#include "board.h"
#include "delay.h"
#include "usart.h"
#include "Emm_V5.h"

int main(void)
{
  //��ʼ����������
	board_	init();

	//�ϵ���ʱ2��ȴ�Emm_V5.0�ջ���ʼ�����
	delay_ms(2000);

	//λ��ģʽ������CW���ٶ�1000RPM�����ٶ�0����ʹ�üӼ���ֱ����������������3200��16ϸ���·���3200��������תһȦ��������˶�
  Emm_V5_Pos_Control(1, 0, 1000, 0, 3200, 0, 0);
	
	//�ȴ���������������ݻ���������rxCmd�ϣ�����ΪrxCount
	while(rxFrameFlag == false); rxFrameFlag = false;

	//WHILEѭ��
	while(1)
	{
	}
}
