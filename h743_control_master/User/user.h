#include "stdbool.h"
#include "emm42/emm42.h"
#include "Emm_V5.h"

#define uartAGX huart1
#define uartPushControlP huart2
#define uartFull huart3
#define uartPushControlQ huart4
#define uartMotorC huart5
#define uartMotorD huart6
#define uartPullingPlateMotor huart7
#define uartMotorB huart8
#define uartTurnMotor huart9
#define uartMotorA huart10

extern emm42_motor motorA, motorB, motorC, motorD;
extern uint16_t m1_encoder, m2_encoder;

extern int A, B, C, D;
extern uint8_t S;

int emm42_motor_init();
bool ABCDMotorStop();

int limit(int data, int rangeMax, bool allowNeg);
bool upMotorsSpeedControl();
bool downMotorsSpeedControl();

bool servoTrun(uint8_t servoNum, uint16_t angle);
bool turnToBin(binTypeDef type);
bool turnMotorControl();
bool downDoorControl(uint8_t open);
bool pullingPlateMotorControl(bool open);

void updatePStatus();
void updateQStatus();