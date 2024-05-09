/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define START_TASK_PRIO 1
#define START_TASK_STACK_SIZE 128
#define TASK1_PRIO 2
#define TASK1_STACK_SIZE 128
#define TASK2_PRIO 3
#define TASK2_STACK_SIZE 128
#define TASK3_PRIO 4
#define TASK3_STACK_SIZE 128
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t startTaskHandle;
const osThreadAttr_t startTask_attributes = {
  .name = "startTask",
  .stack_size = START_TASK_STACK_SIZE * 4,
  .priority = (osPriority_t) START_TASK_PRIO,
};

osThreadId_t task1Handle;
const osThreadAttr_t task1_attributes = {
  .name = "task1",
  .stack_size = TASK1_STACK_SIZE * 4,
  .priority = (osPriority_t) TASK1_PRIO,
};

osThreadId_t task2Handle;
const osThreadAttr_t task2_attributes = {
  .name = "task2",
  .stack_size = TASK2_STACK_SIZE * 4,
  .priority = (osPriority_t) TASK2_PRIO,
};

osThreadId_t task3Handle;
const osThreadAttr_t task3_attributes = {
  .name = "task3",
  .stack_size = TASK3_STACK_SIZE * 4,
  .priority = (osPriority_t) TASK3_PRIO,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
// 任务1, 2, 3 的定义
void task1(void *pvParameters);
void task2(void *pvParameters);
void task3(void *pvParameters);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  //线程一,LED 500ms
  void task1(void* pvParameters)
  {
    while(1)
    {
      LED0_TOGGLE();
      vTaskDelay(500);
    }
  }

  //线程二,LED 200ms
  void task2(void* pvParameters)
  {
    while(1)
    {
      LED1_TOGGLE();
      vTaskDelay(200);
    }
  }

  //线程三,判断KEY0按下删除task1
  void task3(void* pvParameters)
  {
    uint8_t key=0;
    while(1)
    {
      key=key_scan(0);
      if(key==KEY0_PRES && task_handler != NULL)
      {
        vTaskDelete(task1_handler);
      }
      vTaskDelay(10);
    }
  }
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  void (*start_tasks[])(void *) = {task1, task2, task3}; // 任务函数数组
  osThreadAttr_t *task_attributes[] = {&task1_attributes, &task2_attributes, &task3_attributes}; // 任务属性数组
  osThreadId_t *task_handles[] = {&task1Handle, &task2Handle, &task3Handle}; // 任务句柄数组
  for (size_t i = 0; i < sizeof(start_tasks) / sizeof(start_tasks[0]); i++)
  {
       *task_handles[i] = osThreadNew(start_tasks[i], NULL, task_attributes[i]); // 创建3个任务线程
  }
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  while(1)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */