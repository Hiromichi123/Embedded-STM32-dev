#include "pack.h"

void pack()
{
		//抬升4000
	  Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 800, 200, 4000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 800, 200, 4000, false, false);
	  HAL_Delay(2000);
	
		//包装
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2400); //左右舵机前进180
	  HAL_Delay(2000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,600); //左右舵机归0
	  HAL_Delay(200);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2400); //前后舵机前进180
	  HAL_Delay(2000);
	
	  //下降1000
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,600); //前后舵机0
	  HAL_Delay(200);
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
	  HAL_Delay(500);
    
		//回800封箱
		Emm_V5_Pos_Control(&uartHorizon, 1, 0, 800, 200, 800, false, false);
	  HAL_Delay(3000);
		
		//下降500断胶带
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
		HAL_Delay(1000);
		
		//水平电机反向800回0
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(1000);
		
	  //抬升4500回0
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, 5500, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200, 5500, false, false);
	  HAL_Delay(5000);
}
