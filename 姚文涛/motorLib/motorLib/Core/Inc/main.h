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
#define DIR_L1_Pin GPIO_PIN_13
#define DIR_L1_GPIO_Port GPIOC
#define DIR_L2_Pin GPIO_PIN_14
#define DIR_L2_GPIO_Port GPIOC
#define MOTOR_R_Pin GPIO_PIN_0
#define MOTOR_R_GPIO_Port GPIOA
#define MOTOR_L_Pin GPIO_PIN_1
#define MOTOR_L_GPIO_Port GPIOA
#define KEY5_Pin GPIO_PIN_0
#define KEY5_GPIO_Port GPIOB
#define KEY5_EXTI_IRQn EXTI0_IRQn
#define KEY4_Pin GPIO_PIN_1
#define KEY4_GPIO_Port GPIOB
#define KEY4_EXTI_IRQn EXTI1_IRQn
#define STBY_Pin GPIO_PIN_2
#define STBY_GPIO_Port GPIOB
#define SPI_NSS_Pin GPIO_PIN_12
#define SPI_NSS_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_13
#define KEY3_GPIO_Port GPIOB
#define KEY3_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_Pin GPIO_PIN_8
#define KEY2_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_15
#define KEY1_GPIO_Port GPIOA
#define KEY1_EXTI_IRQn EXTI15_10_IRQn
#define ENCODER_R1_Pin GPIO_PIN_4
#define ENCODER_R1_GPIO_Port GPIOB
#define ENCODER_R2_Pin GPIO_PIN_5
#define ENCODER_R2_GPIO_Port GPIOB
#define ENCODER_L1_Pin GPIO_PIN_6
#define ENCODER_L1_GPIO_Port GPIOB
#define ENCODER_L2_Pin GPIO_PIN_7
#define ENCODER_L2_GPIO_Port GPIOB
#define DIR_R1_Pin GPIO_PIN_8
#define DIR_R1_GPIO_Port GPIOB
#define DIR_R2_Pin GPIO_PIN_9
#define DIR_R2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
