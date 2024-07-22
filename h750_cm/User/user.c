#include "user.h"
#include <stdio.h>
#include<pack.h>
void setup() {
	  //传送带通道初始化
	  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); //DIR高电平正转
	  
	  
	  //步进电机通道初始化  方向控制引脚pe10
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET);
	//sg90通道初始化
	  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
	  //机械臂通道初始化
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	
	
	  //开机延时
	  //HAL_Delay(5000);
	
	  //抬升7000
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 1000, 200, PREAMO, false, false);
	HAL_Delay(10);
	Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 1000, 200, PREAMO, false, false);
	HAL_Delay(1000);
		
		//开启传送带
		belt_start();
	  	HAL_Delay(2000);
		
		printf("init complete!");
}

void loop()
{
		static int key2_tick, process=1, key_state;
	
		key_state = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_10);
		if(key_state == 0&&key2_tick-HAL_GetTick()>100)
		{
			flag++;
			key2_tick = HAL_GetTick();
			printf("%d",flag);
		}
		
	  if(flag == 1 && process == 1)
		{
			printf("belt stop");
		  belt_stop();
	      rm_work();
			process++;
			printf("rm_work success!");
			HAL_Delay(1000);
		}
		else if(flag == 2 && process == 2)
		{
			belt_start();
			process++;
			printf("belt_start again");
			HAL_Delay(1000);
		}
		else if(flag == 3 && process == 3)
		{
			printf("pack start");
		  belt_stop();
		  pack();
			belt_start();
			process++;
			HAL_Delay(1000);
		}
}
