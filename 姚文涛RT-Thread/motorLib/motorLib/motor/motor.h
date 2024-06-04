#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stdint.h"
#include "PID.h"

#define OPEN_TB6612 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1)

#define FILTER_RATE_1 				(0.3)
#define FILTER_RATE_2 				(0.3)
#define MOTOR_SPEED_RERATIO 	(30)
#define PULSE_PRE_ROUND				(11)
#define RADIUS_OF_TYRE 				(33.5)
#define LINE_SPEED_C 					(RADIUS_OF_TYRE * 2 * 3.14159)

#define ENCODER_TIM3 htim3
#define RELOADVALUE_R __HAL_TIM_GetAutoreload(&ENCODER_TIM4)
#define COUNTERNUM_R __HAL_TIM_GetCounter(&ENCODER_TIM4)

#define ENCODER_TIM4 htim4
#define RELOADVALUE_L __HAL_TIM_GetAutoreload(&ENCODER_TIM3)
#define COUNTERNUM_L __HAL_TIM_GetCounter(&ENCODER_TIM3)


typedef enum __Motor_Control_Type
{
	Motor_Control_Velocity = 0,
	Motor_Control_Position
}Motor_Conrol_Type;

typedef struct __Motor
{
	int num;
	int lastCount;
  int nowCount;
	int totalCount;
  int overflowNum;
	int pwm;
	int direction;
	float velocity;
	float angle;
	float targetAngle;
	float targetVelocity;
	Motor_Conrol_Type motorCtrlType;
}Motor_Typedef;

extern Motor_Typedef leftMotor, rightMotor;

void Motor_Init          (void);
void Motor_PWM_Set       (Motor_Typedef* motor, int PWM);
void Motor_Velocity_Set  (Motor_Typedef* motor, PID_Typedef* PID);
void Motor_Angle_Set	   (Motor_Typedef* motor, PID_Typedef* PID);
void Motor_Run_Distance  (Motor_Typedef* motor, PID_Typedef* PID, float meters);

#endif
