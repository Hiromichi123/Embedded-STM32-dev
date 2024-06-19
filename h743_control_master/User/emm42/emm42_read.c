#include "main.h"
#include "emm42.h"

/**
  * @brief 读取编码器数据
  * @note 读取位置传感器的数值，数据类型为uint16_t，范围为0-65535
  * @param 电机信息结构体，需要保存的编码器数据地址
  * @retval 成功标志
  */
int emm42ReadEncoder(emm42_motor motor, uint16_t* dataOfEncoder){
    command readCommand;
    readCommand.commandByte = 0x30;
    readCommand.paramsLength = 0;
    emmMotorSend(motor, readCommand);
    UChar dataBack[4];
    int dataBackLength=4;

    HAL_UART_Receive(motor.uart, (uint8_t *)dataBack, dataBackLength, HAL_MAX_DELAY);

    if(dataBack[0] == motor.address && dataBack[3] == motor.checkByte){
        *dataOfEncoder = (dataBack[1] << 8) | dataBack[2];
        return SUCCESS;
    }
    return ERROR;
}

/**
  * @brief 读取位置数据
  * @note 读取电机的实时位置，即对应小屏幕上的第1行的数据，数据类型为int32_t，范围为-2147483647-2147483647
  * @param 电机信息结构体，需要保存的位置数据地址
  * @retval 成功标志
  */
int emm42ReadPosition(emm42_motor motor, int32_t* dataOfPosition){
    command readCommand;
    readCommand.commandByte = 0x36;
    readCommand.paramsLength = 0;
    emmMotorSend(motor, readCommand);
    UChar dataBack[6];
    int dataBackLength=6;
#ifdef TM4
    UChar *p=dataBack;
    for (int i=0; i<dataBackLength; i++){
        *p = UARTCharGet(*motor.uart);
        p++;
    }
#endif // TM4
#ifdef STM32
    HAL_UART_Receive(motor.uart, (uint8_t *)dataBack, dataBackLength, HAL_MAX_DELAY);
#endif // STM32
    if(dataBack[0] == motor.address && dataBack[5] == motor.checkByte){
        *dataOfPosition = (dataBack[1] << 24) | (dataBack[2] << 16) | (dataBack[3] << 8) | dataBack[4];
        return SUCCESS;
    }
    return ERROR;
}
