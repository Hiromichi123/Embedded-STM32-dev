#include "user.h"

void setup() {
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	  HAL_Delay(3000);
}

void loop() {
	  //抬升4000
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, 4000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200, 4000, false, false);
	  HAL_Delay(4000);
	
	  //下降2000
	  Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 2000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 2000, false, false);
	  HAL_Delay(2000);
	
		//包装
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2000); //左右舵机转到180
	  HAL_Delay(2000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,500); //左右舵机转到0
	  HAL_Delay(1000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2000); //前后舵机转到180
	  HAL_Delay(2000);
	
	  //下降1000
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
	  HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,500); //前后舵机转到0
	  HAL_Delay(500);
    
		//左右来回800
		Emm_V5_Pos_Control(&uartHorizon, 1, 0, 800, 200, 800, false, false);
	  HAL_Delay(3000);
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(3000);
		
		//下降1000
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
		HAL_Delay(2000);
}
