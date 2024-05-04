/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR_X_Pin GPIO_PIN_0
#define MOTOR_X_GPIO_Port GPIOA
#define MOTOR_Y_Pin GPIO_PIN_1
#define MOTOR_Y_GPIO_Port GPIOA
#define KEY1_RESET_Pin GPIO_PIN_4
#define KEY1_RESET_GPIO_Port GPIOA
#define KEY1_RESET_EXTI_IRQn EXTI4_IRQn
#define ENCODER_L1_Pin GPIO_PIN_6
#define ENCODER_L1_GPIO_Port GPIOA
#define DIR_X2_Pin GPIO_PIN_0
#define DIR_X2_GPIO_Port GPIOB
#define DIR_X1_Pin GPIO_PIN_1
#define DIR_X1_GPIO_Port GPIOB
#define DIR_Y2_Pin GPIO_PIN_2
#define DIR_Y2_GPIO_Port GPIOB
#define SPI_NSS_Pin GPIO_PIN_12
#define SPI_NSS_GPIO_Port GPIOB
#define DIR_Y1_Pin GPIO_PIN_13
#define DIR_Y1_GPIO_Port GPIOB
#define KEY3_MODE_Pin GPIO_PIN_14
#define KEY3_MODE_GPIO_Port GPIOB
#define KEY3_MODE_EXTI_IRQn EXTI15_10_IRQn
#define KEY4_STOP_Pin GPIO_PIN_15
#define KEY4_STOP_GPIO_Port GPIOB
#define KEY4_STOP_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_START_Pin GPIO_PIN_8
#define KEY2_START_GPIO_Port GPIOA
#define KEY2_START_EXTI_IRQn EXTI9_5_IRQn
#define ENCODER_L2_Pin GPIO_PIN_5
#define ENCODER_L2_GPIO_Port GPIOB
#define ENCODER_R1_Pin GPIO_PIN_6
#define ENCODER_R1_GPIO_Port GPIOB
#define ENCODER_R2_Pin GPIO_PIN_7
#define ENCODER_R2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
