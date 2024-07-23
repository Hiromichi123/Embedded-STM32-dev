#include "pack.h"
#include "user.h"

void push()
{	
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 300); //arr=600, ռ�ձ�50%
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET); //��ת
	HAL_Delay(PushTime);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0); //ռ�ձ�0
}

void back()
{
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 300); //arr=600, ռ�ձ�50%
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET); //��ת
	HAL_Delay(PushTime);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0); //ռ�ձ�0
}

void pack()
{
		//̧��4000
	  Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 800, 200, DOWNAMO, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 800, 200, DOWNAMO, false, false);
	  HAL_Delay(2000);

		//��װ
	  push();
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2400); //���Ҷ��ǰ��180
		//   HAL_Delay(2000);g
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,600); //���Ҷ����0
		//   HAL_Delay(200);
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2400); //ǰ����ǰ��180
		//   HAL_Delay(2000);
	
	  //�½�1000
		
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, TAPEAMO, false, false);
		HAL_Delay(10);
		Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, TAPEAMO, false, false);
	  	HAL_Delay(500);
    
		//��800����
		Emm_V5_Pos_Control(&uartHorizon, 1, 0, 800, 200, 800, false, false);
	  HAL_Delay(3000);
		
		//�½�500�Ͻ���
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, SNAPAMO, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, SNAPAMO, false, false);
		HAL_Delay(1000);
		
		//ˮƽ�������800��0
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(1000);
		
		//ǰ���Ƹ˻���
		back();
		
	  //�����0
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, (PREAMO-DOWNAMO-TAPEAMO-SNAPAMO), false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200,(PREAMO-DOWNAMO-TAPEAMO-SNAPAMO) , false, false);
	  HAL_Delay(5000);
}
