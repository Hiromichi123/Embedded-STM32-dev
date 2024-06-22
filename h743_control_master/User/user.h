#ifndef USER_H
#define USER_H
#include "stdbool.h"
#include "emm42/emm42.h"
#include "Emm_V5.h"

#define uartHorizon huart4
#define uartVertical huart1

void setup(void);
void loop(void);

void emm42_motor_init(void);
void AllMotorStop(void);
#endif
