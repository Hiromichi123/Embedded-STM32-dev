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
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
// 任务1, 2, 3 的定�??
// 线程�??，PA0点灯500ms
void task1(void* pvParameters)
{
  while(1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
    vTaskDelay(200);
  }
}

// 线程二，PA1点灯200ms
void task2(void* pvParameters)
{
  while(1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    vTaskDelay(200);
  }
}

// 线程三，如果PA2被按下，删除task1
void task3(void* pvParameters)
{
  uint32_t button_state = 0;
  uint32_t last_button_state = 0;
  uint32_t last_debounce_time = 0;
  const uint32_t debounce_delay = 50; // 消抖延迟，单位为毫秒

  while(1)
  {
    button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);

    // 如果读取的按键状态与上一次的状�?�不同，重置消抖计时�??
    if (button_state != last_button_state)
    {
      last_debounce_time = xTaskGetTickCount();
    }

    // 如果消抖计时器超过设定的延迟，认为按键状态已稳定
    if ((xTaskGetTickCount() - last_debounce_time) > debounce_delay)
    {
      // 如果按键被按下，并且task1还存在，删除task1
      if(button_state == GPIO_PIN_SET && task1Handle != NULL)
      {
        vTaskDelete(task1Handle);
        task1Handle = NULL;
      }
    }

    last_button_state = button_state;

    vTaskDelay(10);
  }
}
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
  const osThreadAttr_t *task_attributes[] = {&task1_attributes, &task2_attributes, &task3_attributes}; // 任务属�?�数�??
  osThreadId_t *task_handles[] = {&task1Handle, &task2Handle, &task3Handle}; // 任务句柄数组
  for (size_t i = 0; i < sizeof(start_tasks) / sizeof(start_tasks[0]); i++)
  {
       *task_handles[i] = osThreadNew(start_tasks[i], NULL, task_attributes[i]); // 创建3个任务线�??
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

