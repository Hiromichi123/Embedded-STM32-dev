#include "main.h"
#include "stdio.h"
#include "pid.h"
#include "math.h"

#define MAXSUM 10000000
#define SPEED_DEAD_ZONE 0.3

PID_Typedef veloPID_Y, veloPID_X, anglePID_X, anglePID_Y, gimbalPID_X, gimbalPID_Y;

void PID_Init(PID_Typedef * PID_Variables, float Kp, float Ki, float Kd)
{
	PID_Variables->Kp=Kp;
	PID_Variables->Ki=Ki;
	PID_Variables->Kd=Kd;
	PID_Variables->Error=0;
	PID_Variables->Error_Last=0;
	PID_Variables->Error_Prev=0;
	PID_Variables->Error_Sum=0;
	PID_Variables->Value_Actual=0;
	PID_Variables->Value_Target=0;
}
 
float PID_Control_Dir(PID_Typedef* PID_Variables, float Target, float Value_Feedback)
{
	float outPut;
	PID_Variables->Error = (Target - Value_Feedback);
	PID_Variables->Error_Sum = PID_Variables->Error_Sum + PID_Variables->Error;
	PID_Variables->Error_Sum=(PID_Variables->Error_Sum > MAXSUM)?MAXSUM:PID_Variables->Error_Sum;
	PID_Variables->Error_Sum=(PID_Variables->Error_Sum < -MAXSUM)?-MAXSUM:PID_Variables->Error_Sum;
	outPut = (PID_Variables->Kp) * (PID_Variables->Error)
				 + (PID_Variables->Ki) * (PID_Variables->Error_Sum)
				 + (PID_Variables->Kd) * (PID_Variables->Error - PID_Variables->Error_Last);
	PID_Variables->Error_Last = PID_Variables->Error;
	return outPut;
}

float PID_Control_Incre(PID_Typedef* PID_Variables, float Target, float Value_Feedback)
{
	PID_Variables->Error=(Target - Value_Feedback);
	PID_Variables->Value_Actual+=(PID_Variables->Kp * PID_Variables->Error - PID_Variables->Error_Last)
													+(PID_Variables->Ki * (PID_Variables->Error))
													+(PID_Variables->Kd * (PID_Variables->Error + PID_Variables->Error_Prev - 2*PID_Variables->Error_Last));
	PID_Variables->Error_Prev = PID_Variables->Error_Last;
	PID_Variables->Error_Last = PID_Variables->Error;
	return PID_Variables->Value_Actual;
}
