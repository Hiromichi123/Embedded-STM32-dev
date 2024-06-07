#include "board.h"
#include "delay.h"
#include "usart.h"
#include "Emm_V5.h"

int main(void)
{
  //初始化板载外设
	board_init();

	//上电延时2秒等待Emm_V5.0闭环初始化完毕
	delay_ms(2000);

	//位置模式：方向CW，速度1000RPM，加速度0（不使用加减速直接启动），脉冲数3200（16细分下发送3200个脉冲电机转一圈），相对运动
  Emm_V5_Pos_Control(1, 0, 1000, 0, 3200, 0, 0);
	
	//等待返回命令，命令数据缓存在数组rxCmd上，长度为rxCount
	while(rxFrameFlag == false); rxFrameFlag = false;

	//WHILE循环
	while(1)
	{
	}
}
