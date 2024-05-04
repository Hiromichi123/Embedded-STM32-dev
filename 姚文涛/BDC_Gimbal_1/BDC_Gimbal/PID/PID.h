#ifndef PID_H
#define PID_H

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float Value_Target;
	float Value_Actual;
	float Error_Sum;
	float Error;
	float Error_Last;
	float Error_Prev;
}PID_Typedef;

extern PID_Typedef veloPID_Y, veloPID_X, anglePID_X, anglePID_Y, gimbalPID_X, gimbalPID_Y;


void PID_Init(PID_Typedef * PID_Variables, float Kp, float Ki, float Kd);
float PID_Control_Dir(PID_Typedef* PID_Variables, float Target, float Value_Feedback);
float PID_Control_Incre(PID_Typedef* PID_Variables, float Target, float Value_Feedback);
#endif
