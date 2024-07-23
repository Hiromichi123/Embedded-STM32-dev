#include "pack.h"
#include "user.h"

void push()
{	
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 300); //arr=600, 占空比50%
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET); //正转
	HAL_Delay(PushTime);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0); //占空比0
}

void back()
{
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 300); //arr=600, 占空比50%
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET); //反转
	HAL_Delay(PushTime);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 0); //占空比0
}

void pack()
{
		//抬升4000
	  Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 800, 200, DOWNAMO, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 800, 200, DOWNAMO, false, false);
	  HAL_Delay(2000);

		//包装
	  push();
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,2400); //左右舵机前进180
		//   HAL_Delay(2000);g
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2,600); //左右舵机归0
		//   HAL_Delay(200);
		//   __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,2400); //前后舵机前进180
		//   HAL_Delay(2000);
	
	  //下降1000
		
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, TAPEAMO, false, false);
		HAL_Delay(10);
		Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, TAPEAMO, false, false);
	  	HAL_Delay(500);
    
		//回800封箱
		Emm_V5_Pos_Control(&uartHorizon, 1, 0, 800, 200, 800, false, false);
	  HAL_Delay(3000);
		
		//下降500断胶带
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, SNAPAMO, false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, SNAPAMO, false, false);
		HAL_Delay(1000);
		
		//水平电机反向800回0
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(1000);
		
		//前后推杆回零
		back();
		
	  //整体回0
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, (PREAMO-DOWNAMO-TAPEAMO-SNAPAMO), false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200,(PREAMO-DOWNAMO-TAPEAMO-SNAPAMO) , false, false);
	  HAL_Delay(5000);
}
