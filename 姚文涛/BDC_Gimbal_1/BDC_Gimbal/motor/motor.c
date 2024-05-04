#include "motor.h"
#include "main.h"
#include "math.h"
#include "tim.h"
#include "stm32f4xx_hal_tim.h"
#include "stdio.h"
#include "pid.h"
#include "uart_com.h"
#include "control.h"

#define FILTER_NUM 5


int yVeloFilter[FILTER_NUM] = {0};
int xVeloFilter[FILTER_NUM] = {0};

Motor_Typedef yMotor, xMotor;

void Motor_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim9);
	HAL_TIM_Encoder_Start(&ENCODER_TIM3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENCODER_TIM4, TIM_CHANNEL_ALL);
	__HAL_TIM_ENABLE_IT(&ENCODER_TIM3,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&ENCODER_TIM4,TIM_IT_UPDATE);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	
	PID_Init(&veloPID_X, 45, 4.2, 23);
	PID_Init(&veloPID_Y, 36, 4.5, 23);
	PID_Init(&anglePID_X, 24, 0.0, 0.7);
	
	yMotor.num = 0;
	xMotor.num = 1;
	yMotor.velocity = 0;
	xMotor.velocity = 0;
	yMotor.totalCount = 0;
	xMotor.totalCount = 0;
	yMotor.overflowNum = 0;
	xMotor.overflowNum = -1;
	TIM4->CNT = 65534;
	TIM3->CNT = 1;
	yMotor.nowCount = 0;
	xMotor.nowCount = 0;
	yMotor.lastCount = 0;
	xMotor.lastCount = 0;
	yMotor.totalCount = 0;
	xMotor.totalCount = 0;
	yMotor.angle = 0;
	xMotor.angle = 0;
}

void Motor_PWM_Set(Motor_Typedef* motor, int PWM)
{
	if(motor->num == 0) // left motor
	{
		if(PWM > 1000)PWM = 1000;
    if(PWM < -1000)PWM = -1000;
    if(PWM > 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
    }
    if(PWM < 0)
    {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
    }
    TIM5->CCR2 = (int)fabs((float)PWM);
	}
	else if(motor->num == 1)
	{
		if(PWM > 1000)PWM = 1000;
    if(PWM < -1000)PWM = -1000;
    if(PWM < 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
    }
    if(PWM > 0)
    {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
    }
    TIM5->CCR1 = (int)fabs((float)PWM);
	}
}

void Motor_Velocity_Set(Motor_Typedef* motor, PID_Typedef* PID, float targetVelo)
{
	int pwm;
	pwm = (int)PID_Control_Dir(PID, targetVelo, motor->velocity);
	Motor_PWM_Set(motor, pwm);
}

void Motor_Angle_Set(Motor_Typedef* motor, PID_Typedef* PID, float targetAngle)  // tgtAngle:xPI
{
	int velo;
	velo = (int)PID_Control_Dir(PID, targetAngle, motor->angle);
	Motor_Velocity_Set(motor, PID, velo);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	float sumLeft = 0, sumRight = 0;
	if(htim == &htim9)
	{		
		yMotor.nowCount = COUNTERNUM_L + yMotor.overflowNum * 65535;
		xMotor.nowCount = COUNTERNUM_R + xMotor.overflowNum * 65535;
		
		yMotor.totalCount = yMotor.nowCount - yMotor.lastCount;
		xMotor.totalCount = xMotor.nowCount - xMotor.lastCount;
		
		yMotor.velocity = ((float)(yMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND)) * 2 * 3.14159 * 100);
		xMotor.velocity = -((float)(xMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND)) * 2 * 3.14159 * 100);
		
		// Speed Filter
		for(uint8_t i=FILTER_NUM-1;i>0;i--)
		{
			yVeloFilter[i] = yVeloFilter[i-1];
			xVeloFilter[i] = xVeloFilter[i-1];
			sumLeft += yVeloFilter[i];
			sumRight += xVeloFilter[i];
		}
		yVeloFilter[0] = yMotor.velocity;
		xVeloFilter[0] = xMotor.velocity;
		sumLeft += yMotor.velocity;
		sumRight += xMotor.velocity;
		
		yMotor.velocity = sumLeft/FILTER_NUM;
		xMotor.velocity = sumRight/FILTER_NUM;
		
		// Calculate angle
		yMotor.angle += yMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND) * 2 * 3.14159;
		xMotor.angle -= xMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND) * 2 * 3.14159;
		
		yMotor.lastCount = yMotor.nowCount;
		xMotor.lastCount = xMotor.nowCount;
		
		printf("%.2f,%.2f\r\n",xMotor.velocity, yMotor.velocity);
		//printf("%d,%d\r\n",yMotor.nowCount, xMotor.nowCount);

//		Motor_Angle_Set(&xMotor, &anglePID_X, 0.7);
		UARTCOM_GetData(&uart6_com);
		Gimbal_Update(&myGimbal);
		float veloX = PID_Control_Dir(&gimbalPID_X, 0, uart6_com.data[0]);
		float veloY = -PID_Control_Dir(&gimbalPID_Y, 0, uart6_com.data[1]);
		Motor_Velocity_Set(&yMotor, &veloPID_Y, veloY);
		Motor_Velocity_Set(&xMotor, &veloPID_X, veloX);
		
	}
	if(htim == &htim3)  	// Left Encoder Interrupt
	{
		if(COUNTERNUM_L > RELOADVALUE_L / 2)  // Down Overflow
		{
			yMotor.overflowNum--;
			//printf("Encoder_L Down Overflow!\n");
		}
		else	// Up Overflow
		{
			yMotor.overflowNum++;
			//printf("Encoder_L Up Overflow!\n");
		}
		
	}
	if(htim == &htim4)  // Right Encoder Interrupt
	{
		if(COUNTERNUM_R > RELOADVALUE_R / 2)  // Down Overflow
		{
			xMotor.overflowNum--;
		}
		else	// Up Overflow
		{
			xMotor.overflowNum++;
		}
	}
}
