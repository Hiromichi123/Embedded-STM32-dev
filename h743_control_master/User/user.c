#include "main.h"
#include "usart.h"
#include "tim.h"

#include "user.h"

void setup() {
    // 张大头智控初始化
    emm42_motor_init();
    // ABCD舵机初始化
    ABCDMotorStop();
    // 舵盘电机回零
    Emm_V5_Origin_Trigger_Return(&uartTurnMotor, 1, 0, false);
    HAL_Delay(10);
    // 抽拉板电机回零
    Emm_V5_Origin_Trigger_Return(&uartPullingPlateMotor, 2, 2, false);

    HAL_Delay(3000);

    // 清空串口缓冲器，并开启接收中断
    while (HAL_UART_Receive(&uartAGX, uart_AGX_rxbuf, 1, 1) == HAL_OK) {}
    HAL_UART_Receive_IT(&uartAGX, uart_AGX_rxbuf, 1);
    while (HAL_UART_Receive(&uartFull, uart_full_rxbuf, 1, 1) == HAL_OK) {}
    HAL_UART_Receive_IT(&uartFull, uart_full_rxbuf, 1);
    while (HAL_UART_Receive(&uartPushControlP, uart_pushP_rxbuf, 1, 1) == HAL_OK) {}
    HAL_UART_Receive_IT(&uartPushControlP, uart_pushP_rxbuf, 1);
    while (HAL_UART_Receive(&uartPushControlQ, uart_pushQ_rxbuf, 1, 1) == HAL_OK) {}
    HAL_UART_Receive_IT(&uartPushControlQ, uart_pushQ_rxbuf, 1);
}

void loop() {
    upMotorsSpeedControl();
    downMotorsSpeedControl();
    turnMotorControl();
    updatePStatus();
    updateQStatus();

    if (HAL_GetTick() - T1 > 200 && HAL_GetTick() - T2 > 200) {
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
    }

    // 定时串口打印
    static uint32_t last_print_t;
    if (isBaseStatusNew() || HAL_GetTick() - last_print_t > 100) {
        int t1 = (int) (HAL_GetTick() - T1);
        if (t1 > 10000) {
            t1 = 10000;
        }
        int t2 = (int) (HAL_GetTick() - T2);
        if (t2 > 10000) {
            t2 = 10000;
        }
        UART_printf("@%s %dA %dB %dC %dD %dS %dP %dQ %dF %dT %dt %dI %dJ %dR %dH %dK %dO\r\n",
                    rubbishType2Str[rubbishType], A, B, C, D, S, P, Q, F, t1, t2, I, J, R, H, K, O);
        last_print_t = HAL_GetTick();
    }
}
