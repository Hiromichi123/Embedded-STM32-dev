#include "emm42.h"

/**
  * @brief 开关电机
  * @note 控制闭环电机的使能状态
  * @param 电机信息结构体，开关标志
  * @retval 成功标志
  */
int emm42Enable(emm42_motor motor, bool enable) {
    command sendCommand;
    sendCommand.commandByte = 0xF3;
    sendCommand.params[0] = enable ? 0x01 : 0x00;
    sendCommand.paramsLength = 1;
    emmMotorSend(motor, sendCommand);
    return SUCCESS;
}

/**
  * @brief 设置速度
  * @note 控制闭环电机按照设定的方向、速度和加速度进行一直旋转，加速度是指设置启动和停止时曲线加减速档位，可以减少电机启动和停止的震动
  * @param 电机信息结构体，方向，速度，加速度
  * @retval 成功标志
  */
int emm42SetSpeed(emm42_motor motor, bool direction, uint16_t speed, uint8_t acceleration) {
    command sendCommand;
    sendCommand.commandByte = 0xF6;

    if (speed > 0x4FF) {
        speed = 0x4FF;
    }

    sendCommand.params[0] = (speed & 0xff00) >> 8;
    sendCommand.params[1] = speed & 0x00ff;

    if (direction) {
        sendCommand.params[0] |= 0x10;
    }

    sendCommand.params[2] = acceleration;
    sendCommand.paramsLength = 3;
    emmMotorSend(motor, sendCommand);
    return SUCCESS;
}

/**
  * @brief 位置模式控制
  * @note 控制闭环电机按照设定的方向、速度和加速度进行相对位置运动
  * @param 电机信息结构体，方向，速度，加速度，脉冲数
  * @retval 成功标志
  */
int emm42SetPosition(emm42_motor motor, bool direction, uint16_t speed, uint8_t acceleration, uint32_t pulse, bool wait) {
    command sendCommand;
    sendCommand.commandByte = 0xFD;

    if (speed > 0x4FF) {
        speed = 0x4FF;
    }

    sendCommand.params[0] = (speed & 0xff00) >> 8;
    sendCommand.params[1] = speed & 0x00ff;

    if (direction) {
        sendCommand.params[0] |= 0x10;
    }

    sendCommand.params[2] = acceleration;

    sendCommand.params[3] = (pulse & 0xff0000) >> 16;
    sendCommand.params[4] = (pulse & 0xff00) >> 8;
    sendCommand.params[5] = pulse & 0xff;
    sendCommand.paramsLength = 6;
    emmMotorSend(motor, sendCommand);

    UChar dataBack[3];
    int dataBackLength = 3;

    HAL_UART_Receive(motor.uart, (uint8_t *) dataBack, dataBackLength, 1000);

    if (dataBack[0] == motor.address && dataBack[1]==0x02 && dataBack[2] == motor.checkByte) {
        if(!wait){
            return SUCCESS;
        }
        HAL_UART_Receive(motor.uart, (uint8_t *) dataBack, dataBackLength, 1000);
        if (dataBack[0] == motor.address && dataBack[1]==0x9f && dataBack[2] == motor.checkByte){
            return SUCCESS;
        }
        else{
            return ERROR;
        }
    }
    return ERROR;
}

