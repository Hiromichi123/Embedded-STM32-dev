#include "belt.h"

void belt_start()
{

	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 300); //ccr=600, ռ�ձ�50%
}

void belt_stop()
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,0); //ֹͣ��
}
