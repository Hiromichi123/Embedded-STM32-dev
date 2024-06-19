#ifndef EMM42_H
#define EMM42_H

#include "stdbool.h"
#include "stdint.h"
#include "usart.h"

typedef unsigned char UChar;
#define FORWARD 1
#define BACK 0

// 和emm42通信的结构体
typedef struct {
    UART_HandleTypeDef *uart;
    UChar address;
    UChar checkByte;
} emm42_motor;

// 和emm42通信的命令结构体
typedef struct {
    UChar commandByte;
    UChar params[10];
    unsigned int paramsLength;
} command;

// 初始化EMM电机的UART
int emmMotorUartInit(emm42_motor *motor, UART_HandleTypeDef *uart, UChar address, UChar checkByte);
// 向EMM电机发送命令
int emmMotorSend(emm42_motor motor, command sendCommand);
// 从EMM电机读取编码器数据
int emm42ReadEncoder(emm42_motor motor, uint16_t* dataOfEncoder);
// 从EMM电机读取位置数据
int emm42ReadPosition(emm42_motor motor, int32_t* dataOfPosition);
// 启用或禁用EMM电机
int emm42Enable(emm42_motor motor, bool enable);
// 设置EMM电机的速度
int emm42SetSpeed(emm42_motor motor, bool direction, uint16_t speed, uint8_t acceleration);
// 设置EMM电机的位置
int emm42SetPosition(emm42_motor motor, bool direction, uint16_t speed, uint8_t acceleration, uint32_t pulse, bool wait);

#endif //EMM42_H