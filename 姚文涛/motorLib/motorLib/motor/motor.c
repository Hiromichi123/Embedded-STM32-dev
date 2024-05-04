#include "motor.h"
#include "main.h"
#include "math.h"
#include "tim.h"
#include "stm32f4xx_hal_tim.h"
#include "stdio.h"
#include "pid.h"
#include "control.h"

#define FILTER_NUM 8


int leftVeloFilter[FILTER_NUM] = {0};
int rightVeloFilter[FILTER_NUM] = {0};

Motor_Typedef leftMotor, rightMotor;

void Motor_Init(void)
{
	OPEN_TB6612;
	HAL_TIM_Base_Start_IT(&htim5);
	__HAL_TIM_ENABLE_IT(&ENCODER_TIM3,TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&ENCODER_TIM4,TIM_IT_UPDATE);
	HAL_TIM_Encoder_Start(&ENCODER_TIM3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENCODER_TIM4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start_IT(&ENCODER_TIM3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start_IT(&ENCODER_TIM4,TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	
	leftMotor.num = 0;
	rightMotor.num = 1;
	leftMotor.velocity = 0;
	rightMotor.velocity = 0;
	leftMotor.totalCount = 0;
	rightMotor.totalCount = 0;
	leftMotor.overflowNum = 0;
	rightMotor.overflowNum = 0;
	leftMotor.nowCount = 0;
	rightMotor.nowCount = 0;
	leftMotor.lastCount = 0;
	rightMotor.lastCount = 0;
	leftMotor.totalCount = 0;
	rightMotor.totalCount = 0;
	leftMotor.angle = 0;
	rightMotor.angle = 0;
	
	leftMotor.motorCtrlType = Motor_Control_Velocity;
	rightMotor.motorCtrlType = Motor_Control_Velocity;
}

void Motor_PWM_Set(Motor_Typedef* motor, int PWM)
{
	if(motor->num == 1) // right motor
	{
		if(PWM > 1000)PWM = 1000;
    if(PWM < -1000)PWM = -1000;
    if(PWM > 0)
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 1);
    }
    if(PWM < 0)
    {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, 0);
    }
    TIM2->CCR2 = (int)fabs((float)PWM);
	}
	else if(motor->num == 0)
	{
		if(PWM > 1000)PWM = 1000;
    if(PWM < -1000)PWM = -1000;
    if(PWM < 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
    }
    if(PWM > 0)
    {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
    }
    TIM2->CCR1 = (int)fabs((float)PWM);
	}
}

void Motor_Velocity_Set(Motor_Typedef* motor, PID_Typedef* PID)
{
	int pwm;
	if(motor->motorCtrlType == Motor_Control_Velocity)
	{
		pwm = (int)PID_Control_Dir(PID, motor->targetVelocity, motor->velocity);
		Motor_PWM_Set(motor, pwm);
	}
	else{}
}

void Motor_Angle_Set(Motor_Typedef* motor, PID_Typedef* PID)  // tgtAngle:xPI
{
	int pwm;
	if(motor->motorCtrlType == Motor_Control_Position)
	{
		pwm = (int)PID_Control_Dir(PID, motor->targetAngle, motor->angle);
		Motor_PWM_Set(motor, pwm);
	}
	else{}
}

void Motor_Run_Distance(Motor_Typedef* motor, PID_Typedef* PID, float meters)
{
	if(motor->motorCtrlType == Motor_Control_Position)
	{
		float theta = (meters * 1000) / (float)RADIUS_OF_TYRE;
		motor->targetAngle = theta;
		Motor_Angle_Set(motor, PID);
	}
	else{}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	float sumLeft = 0, sumRight = 0;
	if(htim == &htim5)
	{
		leftMotor.nowCount = COUNTERNUM_L + leftMotor.overflowNum * 65535;
		rightMotor.nowCount = COUNTERNUM_R + rightMotor.overflowNum * 65535;
		
		leftMotor.totalCount = leftMotor.nowCount - leftMotor.lastCount;
		rightMotor.totalCount = rightMotor.nowCount - rightMotor.lastCount;
		
		leftMotor.velocity = ((float)(leftMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND)) * 2 * 3.14159 * 100);
		rightMotor.velocity = -((float)(rightMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND)) * 2 * 3.14159 * 100);
		
		// Speed Filter
		for(uint8_t i=FILTER_NUM-1;i>0;i--)
		{
			leftVeloFilter[i] = leftVeloFilter[i-1];
			rightVeloFilter[i] = rightVeloFilter[i-1];
			sumLeft += leftVeloFilter[i];
			sumRight += rightVeloFilter[i];
		}
		leftVeloFilter[0] = leftMotor.velocity;
		rightVeloFilter[0] = rightMotor.velocity;
		sumLeft += leftMotor.velocity;
		sumRight += rightMotor.velocity;
		
		leftMotor.velocity = sumLeft/FILTER_NUM;
		rightMotor.velocity = sumRight/FILTER_NUM;
		
		// Calculate angle
		leftMotor.angle += leftMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND) * 2 * 3.14159;
		rightMotor.angle -= rightMotor.totalCount / (4.0*MOTOR_SPEED_RERATIO*PULSE_PRE_ROUND) * 2 * 3.14159;
		
		leftMotor.lastCount = leftMotor.nowCount;
		rightMotor.lastCount = rightMotor.nowCount;

		//printf("%.2f,%.2f\r\n",leftMotor.velocity, rightMotor.velocity);
		
		Car_UpdateData(&myCar);
		Car_RunInTimer(&myCar);
		
	}
	if(htim == &htim3)  	// Left Encoder Interrupt
	{
		if(COUNTERNUM_L > RELOADVALUE_L / 2)  // Down Overflow
		{
			leftMotor.overflowNum--;
			//printf("Encoder_L Down Overflow!\n");
		}
		else	// Up Overflow
		{
			leftMotor.overflowNum++;
			//printf("Encoder_L Up Overflow!\n");
		}
		
	}
	if(htim == &htim4)  // Right Encoder Interrupt
	{
		if(COUNTERNUM_R > RELOADVALUE_R / 2)  // Down Overflow
		{
			rightMotor.overflowNum--;
		}
		else	// Up Overflow
		{
			rightMotor.overflowNum++;
		}
		//printf("Encoder_R Full!\n");
	}
}
