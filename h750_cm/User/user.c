#include "user.h"

void setup() {
	  //sg90通道初始化
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
	//机械臂通道初始化
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	
	  HAL_Delay(2000);
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
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2400); //左右舵机转到180 
	  HAL_Delay(2000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,600); //左右舵机转到0
	  HAL_Delay(1000);
	  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2400); //前后舵机转到180
	  HAL_Delay(2000);
	
	  //下降1000
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, 1000, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, 1000, false, false);
	  HAL_Delay(500);
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,600); //前后舵机转到0
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
		HAL_Delay(10000);
}
