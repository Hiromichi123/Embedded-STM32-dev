#include "pack.h"

void pack()
{
		//̧��4000
	  Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 800, 200, 4000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 800, 200, 4000, false, false);
	  HAL_Delay(2000);
	
		//��װ
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2400); //���Ҷ��ǰ��180
	  HAL_Delay(2000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,600); //���Ҷ����0
	  HAL_Delay(200);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2400); //ǰ����ǰ��180
	  HAL_Delay(2000);
	
	  //�½�1000
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,600); //ǰ����0
	  HAL_Delay(200);
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
	  HAL_Delay(500);
    
		//��800����
		Emm_V5_Pos_Control(&uartHorizon, 1, 0, 800, 200, 800, false, false);
	  HAL_Delay(3000);
		
		//�½�500�Ͻ���
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
		HAL_Delay(1000);
		
		//ˮƽ�������800��0
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(1000);
		
	  //̧��4500��0
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, 5500, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200, 5500, false, false);
	  HAL_Delay(5000);
}
