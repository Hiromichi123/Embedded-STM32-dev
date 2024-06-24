#include "user.h"

void setup() {
    // 水平电机回零
    Emm_V5_Origin_Trigger_Return(&uartHorizon, 1, 2, false);
    HAL_Delay(10);
    // 升降电机回零
	  Emm_V5_Origin_Trigger_Return(&uartVertical, 2, 2, false);
    HAL_Delay(10);
    // 传送带电机回零
    Emm_V5_Origin_Trigger_Return(&uartRollbar, 3, 2, false);
    HAL_Delay(10);
}

void loop() {
	Emm_V5_Pos_Control(&uartHorizon, 1, 0, 1000, 100, 1000, false, false);
	HAL_Delay(1000);
	Emm_V5_Pos_Control(&uartHorizon, 1, 1, 1000, 100, 1000, false, false);
	HAL_Delay(1000);
	
    Emm_V5_Pos_Control(&uartVertical, 2, 0, 1000, 100, 1000, false, false);
	  //HAL_Delay(1000);
    Emm_V5_Pos_Control(&uartVertical, 2, 2, 1000, 100, 1000, false, false);
	  //HAL_Delay(1000);
	
    Emm_V5_Pos_Control(&uartRollbar, 3, 0, 1000, 100, 1000, false, false);
	  //HAL_Delay(1000);
	  Emm_V5_Pos_Control(&uartRollbar, 3, 0, 1000, 100, 1000, false, false);
    //HAL_Delay(1000);
}
