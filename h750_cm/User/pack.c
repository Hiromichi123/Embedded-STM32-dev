#include "pack.h"
#include "user.h"

int start_tick = 0;

void stick()
{
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 1500); //�뿪צ
	Emm_V5_Pos_Control(&uartHorizon, 1, 1, 50, 50, 14000, false, false); //ˮƽ���ǰ��?
	HAL_Delay(2000);
	
  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 500); //��צ
	HAL_Delay(1000);
	
	//����������
	for(int i = 500;i<3000;i+=4)
  {
      TIM3->CCR4 = i;
      HAL_Delay(1);
  }
	Emm_V5_Pos_Control(&uartHorizon, 1, 0, 50, 50, 14000, false, false); //ˮƽ�������?

	//�½�500�Ͻ���
	Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, SNAPAMO, false, false);
	HAL_Delay(10);
	Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, SNAPAMO, false, false);
	HAL_Delay(1000);
	
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 1500); //�뿪צ
	
	//����
	Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 500, 200, SNAPAMO, false, false);
	HAL_Delay(10);
	Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 500, 200, SNAPAMO, false, false);
	HAL_Delay(1000);
}

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
	
	  //�½�1000
		Emm_V5_Pos_Control(&uartVertical_1, 1, 0, 500, 200, TAPEAMO, false, false);
		HAL_Delay(10);
		Emm_V5_Pos_Control(&uartVertical_2, 1, 1, 500, 200, TAPEAMO, false, false);
	  HAL_Delay(500);
    
		//�⽺
		stick();
		
		//ˮƽ�������?800��0
	  Emm_V5_Pos_Control(&uartHorizon, 1, 1, 800, 200, 800, false, false);
		HAL_Delay(1000);
		
		//ǰ���Ƹ˻���
		back();
		
	  //�����?0
    Emm_V5_Pos_Control(&uartVertical_1, 1, 1, 800, 200, (PREAMO-DOWNAMO-TAPEAMO-SNAPAMO), false, false);
	  HAL_Delay(10);
	  Emm_V5_Pos_Control(&uartVertical_2, 1, 0, 800, 200,(PREAMO-DOWNAMO-TAPEAMO-SNAPAMO) , false, false);
	  HAL_Delay(5000);
}

void tape_move(void)
{
	
	Emm_V5_Pos_Control(&uartHorizon, 1, 0, 50, 50, 14000, false, false);
	while(HAL_GetTick()-start_tick<4000)
	{
		for(int i = 500;i<2500;i+=4)
		{
			TIM3->CCR4 = i;
			HAL_Delay(1);
		}
	}
}
