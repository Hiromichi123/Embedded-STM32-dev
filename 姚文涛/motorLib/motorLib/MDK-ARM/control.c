#include "control.h"
#include <stdio.h>
#include "mpu9250.h"


MPUData_Typedef mpuData;
Car_Typedef myCar;

void Car_Init(Car_Typedef* myCar)
{
	PID_Init(&speedPID_Left, 30,3.1,10);
  PID_Init(&speedPID_Right,30,3,10);
	PID_Init(&anglePID_Left, 10, 0, 0);
	PID_Init(&anglePID_Right, 10, 0, 0);
	PID_Init(&linePID, 0.015, 0, 0.4);
	PID_Init(&turnPID, 0.2, 0, 5);  // 0.2/0.15, 0, 5
	myCar->LeftMotor = leftMotor;
	myCar->RightMotor = rightMotor;
	myCar->MPU_Data = mpuData;
	
	myCar->followLinePID = linePID;
	myCar->leftPosPID = anglePID_Left;
	myCar->rightPosPID = anglePID_Right;
	myCar->leftVeloPID = speedPID_Left;
	myCar->rightVeloPID = speedPID_Right;
	myCar->turnAnglePID = turnPID;
	
	myCar->Car_Function = Function_Stop;
	
	Motor_Init();
}

/* Remember to get PITCH, ROLL, YAW before using this function! */
void MPU_DataProduce(MPUData_Typedef* mpuData)
{
	if((mpuData->yaw - mpuData->lastYaw) > 180)  /* Clockwise overflow */
	{
		mpuData->yawOverflowNum--;
	}
	else if((mpuData->lastYaw - mpuData->yaw) > 180)  /* Anticlockwise overflow */
	{
		mpuData->yawOverflowNum++;
	}
	mpuData->producedYaw = mpuData->yaw + 360 * mpuData->yawOverflowNum;
	mpuData->lastYaw = mpuData->yaw;
}

void MPU_UpdateData(MPUData_Typedef* mpuData)
{
	mpuData->pitch = imu.pitch;
	mpuData->roll = imu.roll;
	mpuData->yaw = -imu.yaw;
}

void Car_GoStraight(Car_Typedef* car)
{
	if(car->Car_Function == Function_GoStraight)
	{
		car->LeftMotor.targetVelocity = car->Car_Data.velocity;
		car->RightMotor.targetVelocity = car->Car_Data.velocity;
		Motor_Velocity_Set(&(car->LeftMotor), &car->leftVeloPID);
		Motor_Velocity_Set(&(car->RightMotor), &car->rightVeloPID);
	}
}
void Car_RunDistance(Car_Typedef* car)
{
	int cntPeriod = 0;
	float vel = 6.28;
	static int cnt;
	if(car->Car_Function == Function_RunDistance)
	{
		cntPeriod = (int)((car->Car_Data.distance * 100000.0) / (vel * RADIUS_OF_TYRE));
		car->Car_Status.runDistanceStatus = Doing;
		if(cnt < fabs(cntPeriod))
		{
			if(car->Car_Data.distance > 0) 
			{
				car->LeftMotor.targetVelocity = vel;
				car->RightMotor.targetVelocity = vel;
			}
			if(car->Car_Data.distance < 0)
			{
				car->LeftMotor.targetVelocity = -vel;
				car->RightMotor.targetVelocity = -vel;
			}
			Motor_Velocity_Set(&car->LeftMotor, &car->leftVeloPID);
			Motor_Velocity_Set(&car->RightMotor, &car->rightVeloPID);
			cnt++;
		}
		else
		{
			cnt = 0;
			printf("STOP!\n");
			car->Car_Status.runDistanceStatus = Complete;
			car->Car_Function = Function_Stop;
		}
	}
}

void Car_FollowLine(Car_Typedef* car)
{
	float velOut = 0;
	if(car->Car_Function == Function_FollowLine)
	{
		car->Car_Status.followLineStatus = Doing;
		velOut = PID_Control_Dir(&car->followLinePID, 0, car->Car_Data.difFromLine);
		car->LeftMotor.targetVelocity = 9 - velOut;
		car->RightMotor.targetVelocity = 9 + velOut;
		Motor_Velocity_Set(&(car->LeftMotor), &car->leftVeloPID);
		Motor_Velocity_Set(&(car->RightMotor), &car->rightVeloPID);
	}
	else{}
}

/* angle: 
				  Anticlockwise : Positive
					Clockwise     : Negative 
*/
int Car_TurnAngle(Car_Typedef* car)
{
	int velOut = 0, cntPeriod = 100;  /* cntPeriod should be in 100 to 200 */
	float dYaw = 0;
	static float sampleYaw = 0;
	static int sampleFlag = 0, cnt = 0;
	if(car->Car_Function == Function_TurnAngle)
	{
		car->Car_Status.turnAngleStatus = Doing;
		if(sampleFlag == 0)
		{
			sampleFlag = 1;
			sampleYaw = car->MPU_Data.producedYaw;
		}
		dYaw = car->MPU_Data.producedYaw - sampleYaw;
		velOut = PID_Control_Dir(&(car->turnAnglePID), car->Car_Data.turnAngle, dYaw);
//		velOut = PID->Kp * dYaw + PID->Kd * mpuData->gyroZ;
		rightMotor.targetVelocity = 0 + velOut;
		leftMotor.targetVelocity = 0 - velOut;
		Motor_Velocity_Set(&(car->LeftMotor), &car->leftVeloPID);
		Motor_Velocity_Set(&(car->RightMotor), &car->rightVeloPID);
		cnt++;
		//printf("%.2f,%d\r\n",dYaw, cnt);
		if(cnt >= cntPeriod) 
		{
			cnt = 0;
			sampleFlag = 0;
			car->Car_Status.turnAngleStatus = Complete;
			car->Car_Function = Function_Stop;
			return 1;
		}
		else {return 0;}
	}
	else return -1;
}

/* This function should be called in a TIMER! */
void Car_RunInTimer(Car_Typedef* myCar)
{
	Car_GoStraight(myCar);
	Car_FollowLine(myCar);
	Car_TurnAngle(myCar); 
	Car_RunDistance(myCar);
	if(myCar->Car_Function == Function_Stop)
	{
		myCar->Car_Function = Function_GoStraight;
		myCar->Car_Data.velocity = 0;
		Car_GoStraight(myCar);
	}
}
/* This function should also be called in a TIMER, and before calling the 'Car_RunInTimer' */
void Car_UpdateData(Car_Typedef* mycar)
{
	mycar->LeftMotor = leftMotor;
	mycar->RightMotor = rightMotor;
	mycar->MPU_Data = mpuData;
}
