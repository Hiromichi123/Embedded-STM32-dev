#include "user.h"

int UART_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int length;
    char buffer[128];

    length = vsnprintf(buffer, 128, fmt, ap);

    HAL_UART_Transmit(&uartAGX, (uint8_t *) buffer, length, HAL_MAX_DELAY);

    va_end(ap);
    return length;
}

uint8_t uart_AGX_rxbuf[1], uart_full_rxbuf[1], uart_pushP_rxbuf[1], uart_pushQ_rxbuf[1];

void UART_AGX_Handle(uint8_t data) {
    static int value;
    static int symbol = 1;
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    if (data >= '0' && data <= '9') {
        value = value * 10 + data - '0';
    } else if (data == '-') {
        value = 0;
        symbol = -1;
    } else {
        switch (data) {
            case 'R':
                turnToBin(RECYCLABLE);
                break;
            case 'H':
                turnToBin(HAZARDOUS);
                break;
            case 'K':
                turnToBin(KITCHEN);
                break;
            case 'O':
                turnToBin(OTHER);
                break;
            case 'A':
                A = value * symbol;
                break;
            case 'B':
                B = value * symbol;
                break;
            case 'C':
                C = value * symbol;
                break;
            case 'D':
                D = value * symbol;
                break;
            case 'S':
                downDoorControl(value);
                break;
            case 'F':
                F = value == 0 ? 0 : 1;
                HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, !F);
                break;
            case 'P':
                P_AGX = value;
                break;
            case 'Q':
                Q_AGX = value;
                break;
            default:
                break;
        }
        value = 0;
        symbol = 1;
    }
}

void UART_Full_Handle(uint8_t data) {
    static int value;
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    if (data >= '0' && data <= '9') {
        value = value * 10 + data - '0';
    } else {
        switch (data) {
            case 'R':
                R = value;
                break;
            case 'H':
                H = value;
                break;
            case 'K':
                K = value;
                break;
            case 'O':
                O = value;
                break;
            default:
                break;
        }
        value = 0;
    }
}

void UART_P_Handle(uint8_t data) {
    static int value;
    HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
    if (data >= '0' && data <= '9') {
        value = value * 10 + data - '0';
    } else {
        switch (data) {
            case 'P':
                if (value == 0 || value == 1 || value == 2)
                    P_g030 = value;
                break;
            case 'I':
                I = value;
                break;
            default:
                break;
        }
        value = 0;
    }
}

void UART_Q_Handle(uint8_t data) {
    static int value;
    HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
    if (data >= '0' && data <= '9') {
        value = value * 10 + data - '0';
    } else {
        switch (data) {
            case 'P':
                if (value == 0 || value == 1 || value == 2)
                    Q_g030 = value;
                break;
            case 'I':
                J = value;
                break;
            default:
                break;
        }
        value = 0;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &uartAGX) {
        UART_AGX_Handle(*uart_AGX_rxbuf);
        HAL_UART_Receive_IT(&uartAGX, uart_AGX_rxbuf, 1);
    } else if (huart == &uartFull) {
        UART_Full_Handle(*uart_full_rxbuf);
        HAL_UART_Receive_IT(&uartFull, uart_full_rxbuf, 1);
    } else if (huart == &uartPushControlP) {
        UART_P_Handle(*uart_pushP_rxbuf);
        HAL_UART_Receive_IT(&uartPushControlP, uart_pushP_rxbuf, 1);
    } else if (huart == &uartPushControlQ) {
        UART_Q_Handle(*uart_pushQ_rxbuf);
        HAL_UART_Receive_IT(&uartPushControlQ, uart_pushQ_rxbuf, 1);
    }
}
