#include<main.h>

#define Max_angle 180
#define Min_angle 0

// #define A1 TIM2->CCR1
// #define TIM2->CCR2 A2
// #define TIM2->CCR3 A3
// #define TIM3->CCR1 A4
// #define TIM3->CCR2 A5
// #define TIM3->CCR3 A6

// int *a;
// double b;
// void control_single(int* angle_num,double target_angle)
// {
//     if(target_angle>Max_angle) 
//     {
//         target_angle = Max_angle;
//     }
//     if(target_angle<Min_angle)
//     {
//         target_angle = Min_angle;
//     }
//     int angle_to_ccr = 500+(int)target_angle*2000/180;
//     angle_num = angle_to_ccr;
// }
// void control_total()
// {
//     control_single(b,90)
// }
double angle1 = 0;
double angle2 = 0;
double angle3 = 0;
double angle4 = 0;
double angle5 = 0;
double angle6 = 0;

void control_one(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR1=angle_to_CCR;
}
void control_two(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR2=angle_to_CCR;
}
void control_three(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR3=angle_to_CCR;
}
void control_four(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM3->CCR1=angle_to_CCR;
}
void control_five(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM3->CCR2=angle_to_CCR;
}
void control_six(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM3->CCR3=angle_to_CCR;
}
void Control_angle()
{
	control_one(angle1);
	control_two(angle2);
	control_three(angle3);
	control_four(angle4);
	control_five(angle5);
	control_six(angle6);
}
void Start_state()
{
	angle1=180;
	angle2=120;
	angle3=60.5;
	angle4=60.0;
	angle5=1.0;
	angle6=0.0;
	Control_angle();
}
void servo_move(double target,double *angle)
{
	double step = (target-*angle)/100;
	for(int cnt = 0;cnt<100;cnt++)
	{
		*angle+=step;
		Control_angle();
		HAL_Delay(10);
	}
}

void rm_pack()
{		Start_state();
		servo_move(60,&angle2);
		servo_move(60,&angle3);
		servo_move(90,&angle6);
		servo_move(120,&angle2);
		servo_move(90,&angle1);
		servo_move(100,&angle2);
		servo_move(80,&angle4);
		servo_move(80,&angle3);
		servo_move(0,&angle6);
    //夹取物体放入箱子
		servo_move(84,&angle4);
		servo_move(150,&angle2);
		servo_move(50,&angle1);
		servo_move(94,&angle2);
		servo_move(120,&angle4);
		servo_move(64,&angle2);
		servo_move(60,&angle6);
		servo_move(130,&angle2);
		servo_move(86,&angle1);
		servo_move(0,&angle6);
}
void rm_abandon()
{
	Start_state();
	servo_move(50,&angle1);
	servo_move(94,&angle2);
	servo_move(120,&angle4);
	servo_move(64,&angle2);
	servo_move(60,&angle6);
	servo_move(90,&angle2);
	servo_move(90,&angle1);
	servo_move(0,&angle4);
	servo_move(0,&angle2);
	
}