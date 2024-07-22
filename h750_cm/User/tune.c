#include"tune.h"
#include"main.h"
#include<stdio.h>
uint8_t s_msg[1] = {0};
uint32_t time = 0;
uint32_t last_time = 0;
void tune()
{
    static uint32_t time = 0;
    static uint32_t last_time = 0;
    HAL_UART_Receive(&huart8,s_msg,sizeof(s_msg),HAL_MAX_DELAY);
    if(s_msg[1] == 11)
    {
        TIM1->CCR1 = 0;
        time = HAL_GetTick()-last_time;
        last_time = time;
        printf("main.t0.txt=\"stop\"\xff\xff\xff");
        printf("main.n0.val=%d\xff\xff\xff",time);
    }
     else if(s_msg[1] == 12)
    {
        TIM1->CCR2 = 300;
        printf("main.t0.txt=\"start\"\xff\xff\xff");
        
    }
    else if (s_msg[1] == 13)
    {
        HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_13);
        last_time = HAL_GetTick()-time;
    }
    
}