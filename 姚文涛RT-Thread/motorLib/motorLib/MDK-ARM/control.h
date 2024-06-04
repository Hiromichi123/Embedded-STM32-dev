#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "pid.h"
#include "main.h"
#include "motor.h"
#include "math.h"


typedef enum __Car_Function_Type
{
	Function_Stop = 0,
	Function_GoStraight,
	Function_FollowLine,
	Function_TurnAngle,
	Function_RunDistance
}Car_Function_Type;

typedef enum __Car_Action_Status
{
	Idle = 0,
	Doing,
	Complete
}Car_Action_Status;

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

typedef struct __Car_Status
{
	Car_Action_Status turnAngleStatus;
	Car_Action_Status followLineStatus;
	Car_Action_Status runDistanceStatus;
}Car_Status_Type;

typedef struct __Car_Data
{
	int difFromLine;
	float turnAngle;
	float velocity;
	float distance;  /* In units of meters */
}Car_Data_Type;

typedef struct __Car
{
	Car_Status_Type   Car_Status;
	Car_Function_Type Car_Function;
	Car_Data_Type Car_Data;
	
	PID_Typedef leftVeloPID;
	PID_Typedef rightVeloPID;
	PID_Typedef leftPosPID;
	PID_Typedef rightPosPID;
	PID_Typedef followLinePID;
	PID_Typedef turnAnglePID;
	
	Motor_Typedef LeftMotor;
	Motor_Typedef RightMotor;
	
	MPUData_Typedef MPU_Data;
}Car_Typedef;

extern MPUData_Typedef mpuData;
extern Car_Typedef myCar;

void Car_Init					(Car_Typedef* myCar);
void MPU_DataProduce	(MPUData_Typedef* mpuData);
void MPU_UpdateData		(MPUData_Typedef* mpuData);
void Car_GoStraight		(Car_Typedef* car);
void Car_FollowLine		(Car_Typedef* car);
int Car_TurnAngle			(Car_Typedef* car);
void Car_RunDistance	(Car_Typedef* car);
void Car_UpdateData		(Car_Typedef* mycar);
void Car_RunInTimer		(Car_Typedef* myCar);

#endif
