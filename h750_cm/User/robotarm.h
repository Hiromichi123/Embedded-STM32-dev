#ifndef __ROBOT_ARM__
#define  __ROBOT_ARM__

#include"main.h"
extern double angle1;
extern double angle2;
extern double angle3;
extern double angle4;
extern double angle5;
extern double angle6;


void control_one(double angle);
void control_two(double angle);
void control_three(double angle);
void control_four(double angle);
void control_five(double angle);
void control_six(double angle);
void Control_angle(void);
void Start_state(void);
void servo_move(double target,double *angle);
void rm_pack(void);
void rm_abandon(void);
#endif
