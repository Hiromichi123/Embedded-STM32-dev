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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "u8g2.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Max_angle 179.5
#define Min_angle 0.5
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
u8g2_t u8g2;
char OLED1[10];
char OLED2[10];
char OLED3[10];
char OLED4[10];
char OLED5[10];
char OLED6[10];

double angle1=0;
double angle2=0;
double angle3=0;
double angle4=0;
double angle5=0;
double angle6=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
uint32_t keyborad_scan(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

void control_one(double angle);
void control_two(double angle);
void control_three(double angle);
void control_four(double angle);
void control_five(double angle);
void control_six(double angle);
void Control_angle();
void Start_state();


uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,U8X8_UNUSED void *arg_ptr);
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr);
void u8g2_DrawLine(u8g2_t *u8g2, u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1);
void frame(u8g2_t* u8g2,uint8_t first[],uint8_t second[],uint8_t out[]);
void frameutf8(uint8_t first[],uint8_t second[],uint8_t out[]);
/* USER CODE BEGIN PFP */

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
  uint32_t tick=HAL_GetTick();
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
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//1
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);//2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);//3
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);//4
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);//5
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);//6
	
	HAL_TIM_Base_Start_IT(&htim2);
  u8g2_Setup_ssd1306_128x64_noname_1(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	
	TIM2->PSC=83;
	TIM2->ARR=19999;
	TIM4->PSC=83;
	TIM4->ARR=19999;
  Start_state();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		uint32_t key=keyborad_scan();
		if(key!=0)
		{ 
			if(HAL_GetTick()-tick>200) 
			{
		
				tick=HAL_GetTick();
			} 
	 		else {key=0;}
	  }
    if(key==1){angle1=angle1+2;key=0;}
		else if(key==2){angle1=angle1-2;key=0;}
		else if(key==3){angle2=angle2+2;key=0;}
		else if(key==4){angle2=angle2-2;key=0;}
		else if(key==5){angle3=angle3+2;key=0;}
		else if(key==6){angle3=angle3-2;key=0;}
		else if(key==7){angle4=angle4+2;key=0;}
		else if(key==8){angle4=angle4-2;key=0;}
		else if(key==9){angle5=angle5+2;key=0;}
		else if(key==10){angle5=angle5-2;key=0;}
		else if(key==11){angle6=angle6+2;key=0;}
		else if(key==12){angle6=angle6-2;key=0;}
		
		Control_angle();
		
		u8g2_FirstPage(&u8g2);
    u8g2_ClearBuffer(&u8g2);
    do
    {
		u8g2_SetFont(&u8g2,u8g2_font_courR12_tf);
			u8g2_DrawStr(&u8g2, 0, 15, "D1:");
			sprintf(OLED1,"%.1lf",angle1);
			u8g2_DrawStr(&u8g2, 25, 15, OLED1 );
      u8g2_DrawStr(&u8g2, 65, 15, "D2:");
			sprintf(OLED2,"%.1lf",angle2);
			u8g2_DrawStr(&u8g2, 90, 15, OLED2 );
			u8g2_DrawStr(&u8g2, 0, 30, "D3:");
			sprintf(OLED3,"%.1lf",angle3);
			u8g2_DrawStr(&u8g2, 25, 30, OLED3 );
			u8g2_DrawStr(&u8g2, 65, 30, "D4:");
			sprintf(OLED4,"%.1lf",angle4);
			u8g2_DrawStr(&u8g2, 90, 30, OLED4 );
			u8g2_DrawStr(&u8g2, 0, 45, "D5:");
			sprintf(OLED5,"%.1lf",angle5);
			u8g2_DrawStr(&u8g2, 25, 45, OLED5 );
			u8g2_DrawStr(&u8g2, 0, 60, "D6:");
			sprintf(OLED6,"%.1lf",angle6);
			u8g2_DrawStr(&u8g2, 25, 60, OLED6 );
       }while (u8g2_NextPage(&u8g2));
  /* USER CODE END 3 */
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
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
void control_one(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR1=angle_to_CCR;
}
void control_two(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR2=angle_to_CCR;
}
void control_three(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR3=angle_to_CCR;
}
void control_four(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM2->CCR4=angle_to_CCR;
}
void control_five(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM4->CCR1=angle_to_CCR;
}
void control_six(double angle)
{
	if(angle>Max_angle) angle=Max_angle;
	else if(angle<Min_angle) angle=Min_angle;
	int angle_to_CCR=500+(int)angle*2000/180;
	TIM4->CCR2=angle_to_CCR;
}
void Control_angle()
{
	control_one(angle1);
	control_two(angle2);
	control_three(angle3);
	control_four(angle4);
	control_five(angle5);
	control_six(angle6);
}
void Start_state()
{
	angle1=89;
	angle2=20;
	angle3=0.5;
	angle4=170;
	angle5=1;
	angle6=85;
	Control_angle();
}

uint32_t keyborad_scan(void) 
		{ uint8_t press_key=0; 
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0); 
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)) press_key=1;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)) press_key=2;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)) press_key=3;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)) press_key=4;
	    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0); 
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)) press_key=5;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)) press_key=6;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)) press_key=7;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)) press_key=8;
	    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0); 
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)) press_key=9;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)) press_key=10;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)) press_key=11;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)) press_key=12;
	    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1); 
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)) press_key=13;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)) press_key=14;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)) press_key=15;
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)) press_key=16;
	return press_key; 
		}
int fputc(int ch, FILE *f)
	{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	return ch;
	}
int fgetc(FILE *f)
	{
	uint8_t ch = 0;
	HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
	return ch;
	}
	

uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void *arg_ptr)
{
  switch (msg)
  {
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    HAL_Delay(1);
    break;
  case U8X8_MSG_DELAY_MILLI:
    HAL_Delay(arg_int);
    break;
  case U8X8_MSG_GPIO_DC:
    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
    break;
  case U8X8_MSG_GPIO_RESET:
    HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, arg_int);
    break;
  }
  return 1;
}

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
    void *arg_ptr)
{
  switch (msg)
  {
  case U8X8_MSG_BYTE_SEND:
    HAL_SPI_Transmit(&hspi1, (uint8_t *) arg_ptr, arg_int, HAL_MAX_DELAY);
    break;
  case U8X8_MSG_BYTE_INIT:
    break;
  case U8X8_MSG_BYTE_SET_DC:
    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
		HAL_GPIO_WritePin(OLED_NSS_GPIO_Port, OLED_NSS_Pin, GPIO_PIN_RESET);
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
		HAL_GPIO_WritePin(OLED_NSS_GPIO_Port, OLED_NSS_Pin, GPIO_PIN_SET);
    break;
  default:
    return 0;
  }
  return 1;
}
void u8g2_DrawLine(u8g2_t *u8g2, u8g2_uint_t x0, u8g2_uint_t y0, u8g2_uint_t x1, u8g2_uint_t y1);
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
