/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "uart_com.h"
#include "easyTask.h"
#include "control.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>
#include "mpu9250.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
tptask_t mainTask, getMPUDataTask, updateDataTask;
int32_t tick;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void mainTaskHandler(void);
void getMPUDataTaskHandler(void);
void dataUpdateHandler(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	mpu9250_init();
	IMU_Init();
	while(IMU_Calibrate() != 1);

	TP_TaskInit(&mainTask, -1, mainTaskHandler);
	TP_TaskInit(&getMPUDataTask, -1, getMPUDataTaskHandler);
	TP_TaskInit(&updateDataTask, -1, dataUpdateHandler);
		
	HAL_UART_Receive_IT(&huart6, (uint8_t *)&(uart6_com.aRxBuffer), 1);

	Car_Init(&myCar);

	tick = HAL_GetTick();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		TP_TaskHandler();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void mainTaskHandler(void)
{
	if(myCar.Car_Status.turnAngleStatus == Complete)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"1\n", sizeof("1\n"));
		myCar.Car_Status.turnAngleStatus = Idle;
	}
	if(myCar.Car_Status.runDistanceStatus == Complete)
	{
		HAL_UART_Transmit_DMA(&huart1, (uint8_t*)"2\n", sizeof("2\n"));
		myCar.Car_Status.runDistanceStatus = Idle;
	}
//	myCar.Car_Function = Function_GoStraight;
//	myCar.Car_Data.velocity = -5;
}

void getMPUDataTaskHandler(void)
{
	IMUSO3Thread();
	MPU_UpdateData(&mpuData);
	MPU_DataProduce(&mpuData);
}

void dataUpdateHandler(void)
{
	UARTCOM_Get2Data(&uart6_com);
	myCar.Car_Function = uart6_com.data[0];
	if(myCar.Car_Function == Function_RunDistance)
	{
		myCar.Car_Data.distance = uart6_com.data[1] / 100;
	}
	if(myCar.Car_Function == Function_FollowLine)
	{
		myCar.Car_Data.difFromLine = uart6_com.data[1];
	}
	if(myCar.Car_Function == Function_TurnAngle)
	{
		myCar.Car_Data.turnAngle = uart6_com.data[1];
		if(fabs(myCar.Car_Data.turnAngle) == 90)
		{
			myCar.turnAnglePID.Kp = 0.2;
		}
		if(fabs(myCar.Car_Data.turnAngle) == 180)
		{
			myCar.turnAnglePID.Kp = 0.162;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{
//		myCar.Car_Function = Function_TurnAngle;
//		myCar.Car_Data.turnAngle = 180;
//		myCar.turnAnglePID.Kp = 0.162;
		printf("RUNNING!\n");
		myCar.Car_Data.distance = -0.5;
		myCar.Car_Function = Function_RunDistance;
		//HAL_UART_Transmit_DMA(&huart6, (uint8_t*)"2\n", sizeof("2\n"));
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

