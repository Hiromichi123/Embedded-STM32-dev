#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "pid.h"
#include "main.h"
#include "motor.h"
#include "math.h"


typedef struct __mpuData
{
	int yawOverflowNum;
	short gyroX;
	short gyroY;
	short gyroZ;        /* Clockwise: Negative ; Anticlockwise: Positive */
	float pitch;
	float roll;
	float yaw;
	float lastYaw;
	float producedYaw;  /* Clockwise:-- ; Anticlockwise:++ */
}MPUData_Typedef;



typedef struct __Gimbal
{
	PID_Typedef xVeloPID;
	PID_Typedef yVeloPID;
	PID_Typedef xAnglePID;
	PID_Typedef yAnglePID;
	PID_Typedef xFollowPID;
	PID_Typedef yFollowPID;
	
	Motor_Typedef yMotor;
	Motor_Typedef xMotor;
	
	float gimbalVelo_X;
	float gimbalVelo_Y;
	
	MPUData_Typedef MPU_Data;
}Gimbal_Typedef;

extern MPUData_Typedef mpuData;
extern Gimbal_Typedef myGimbal;

void Gimbal_Init(Gimbal_Typedef* gimbal);
void Gimbal_Update(Gimbal_Typedef* gimbal);


#endif
