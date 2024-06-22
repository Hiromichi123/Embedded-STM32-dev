#include "user.h"

void setup() {
    // 张大头智控初始化
    emm42_motor_init();
    // 水平电机回零
    Emm_V5_Origin_Trigger_Return(&uartHorizon, 1, 2, false);
    HAL_Delay(10);
    // 升降电机回零
    Emm_V5_Origin_Trigger_Return(&uartVertical, 2, 2, false);
    HAL_Delay(10);
    // 传送带电机回零
    //Emm_V5_Origin_Trigger_Return(&uartRollbar, 3, 2, false);
    HAL_Delay(10);
}

void loop() {
    //if (HAL_GetTick() - T1 > 200 && HAL_GetTick() - T2 > 200) {
    //    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
    //}
		Emm_V5_En_Control(&uartHorizon, 1, true, false);
    Emm_V5_Pos_Control(&uartHorizon, 1, 0, 100, 10, 1000, false, false);
	
    Emm_V5_En_Control(&uartVertical, 2, true, false);
    Emm_V5_Pos_Control(&uartVertical, 2, 0, 100, 10, 1000, false, false);
    HAL_Delay(1000);
}

emm42_motor motorA, motorB;

void emm42_motor_init(void){
    motorA.uart = &uartHorizon;
    motorA.address = 0x01;
    motorA.checkByte = 0x6B;

    motorB.uart = &uartVertical;
    motorB.address = 0x01;
    motorB.checkByte = 0x6B;
}

void AllMotorStop(void){
    emm42SetSpeed(motorA, FORWARD, 0, 100);
    emm42SetSpeed(motorB, FORWARD, 0, 100);
}
