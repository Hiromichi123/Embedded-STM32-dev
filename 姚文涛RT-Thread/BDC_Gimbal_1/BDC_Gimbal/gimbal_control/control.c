#include "control.h"
#include <stdio.h>
//#include "mpu9250.h"


MPUData_Typedef mpuData;
Gimbal_Typedef myGimbal;

/* Remember to get PITCH, ROLL, YAW before using this function! */
//void MPU_DataProduce(MPUData_Typedef* mpuData)
//{
//	if((mpuData->yaw - mpuData->lastYaw) > 180) 		  /* Clockwise overflow */
//	{
//		mpuData->yawOverflowNum--;
//	}
//	else if((mpuData->lastYaw - mpuData->yaw) > 180)  /* Anticlockwise overflow */
//	{
//		mpuData->yawOverflowNum++;
//	}
//	mpuData->producedYaw = mpuData->yaw + 360 * mpuData->yawOverflowNum;
//	mpuData->lastYaw = mpuData->yaw;
//}

//void MPU_UpdateData(MPUData_Typedef* mpuData)
//{
//	mpuData->pitch = imu.pitch;
//	mpuData->roll = imu.roll;
//	mpuData->yaw = -imu.yaw;
//}


void Gimbal_Init(Gimbal_Typedef* gimbal)
{
	gimbal->MPU_Data = mpuData;
	Motor_Init();
	
	PID_Init(&gimbalPID_X, 0.00085, 0.000, 0.09);
	PID_Init(&gimbalPID_Y, 0.00085, 0, 0.09);
	
	gimbal->xMotor = xMotor;
	gimbal->yMotor = yMotor;
	gimbal->xVeloPID = veloPID_X;
	gimbal->yVeloPID = veloPID_Y;
	gimbal->xAnglePID = anglePID_X;
	gimbal->yAnglePID = anglePID_Y;
	gimbal->xFollowPID = gimbalPID_X;
	gimbal->yFollowPID = gimbalPID_Y;
	
}
/* This function should be called in a TIMER */
void Gimbal_Update(Gimbal_Typedef* gimbal)
{
	gimbal->xMotor = xMotor;
	gimbal->yMotor = yMotor;
	gimbal->MPU_Data = mpuData;
}

void Gimbal_X_Angle_Set(Gimbal_Typedef* gimbal, float targetAngle)
{
	int pwm;
	pwm = (int)PID_Control_Dir(&gimbal->xVeloPID, targetAngle, gimbal->xMotor.angle);
	Motor_PWM_Set(&gimbal->xMotor, pwm);
}

