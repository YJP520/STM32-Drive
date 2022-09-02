/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "user/motor.h"
#include "user/data_trans.h"
#include "user/debug_com.h"
#include "user/oled.h"

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
/* USER CODE BEGIN Variables */
motorInfoType motorInfoList[2];
carInfoType carInfo;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTaskMotor */
osThreadId_t myTaskMotorHandle;
const osThreadAttr_t myTaskMotor_attributes = {
  .name = "myTaskMotor",
  .stack_size = 384 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTaskMotor(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  carInfo.x = 0;
  carInfo.y = 0;
  carInfo.z = 0;
  init_motorInfo(&motorInfoList[0], htim2, htim3, TIM_CHANNEL_2, GPIOC, GPIO_PIN_4, GPIOC, GPIO_PIN_5);
  init_motorInfo(&motorInfoList[1], htim4, htim3, TIM_CHANNEL_1, GPIOA, GPIO_PIN_5, GPIOA, GPIO_PIN_4);
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

  start_data();
  start_motor(motorInfoList, 2);

//  OLED_Init();
//  OLED_preFlash();
//  OLED_flash_format();

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

  /* creation of myTaskMotor */
  myTaskMotorHandle = osThreadNew(StartTaskMotor, NULL, &myTaskMotor_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
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
  motorInfoList[0].pidInfo.TGT = 20;
  motorInfoList[1].pidInfo.TGT = -20;
  /* Infinite loop */
  for(;;)
  {
//    printf("ENC\tTGT\tPWM\n");
//    for(int i=0; i<2; i++){
//      printf("%-4d\t%-4d\t%-6d\n", motorInfoList[i].pidInfo.ENC, motorInfoList[i].pidInfo.TGT, motorInfoList[i].pidInfo.PWM);
//    }
//    printf("\n");
//    printf("%d,%d,%d\r\n",motorInfoList[0].pidInfo.PWM/1000, motorInfoList[0].pidInfo.ENC, motorInfoList[0].pidInfo.TGT);
    printf("%d,%d\r\n",motorInfoList[0].pidInfo.ENC, motorInfoList[0].pidInfo.TGT);
//    show_info(motorInfoList[0].pidInfo.ENC, 1+8*6, 0);
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskMotor */
/**
* @brief Function implementing the myTaskMotor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskMotor */
void StartTaskMotor(void *argument)
{
  /* USER CODE BEGIN StartTaskMotor */
  /* Infinite loop */
  for(;;)
  {
//    Kinematic_Analysis_4(motorInfoList, &carInfo);
    motor_run(motorInfoList, 2);
    osDelay(10);
  }
  /* USER CODE END StartTaskMotor */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

