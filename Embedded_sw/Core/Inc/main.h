/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

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
void start_cycle_count();
void stop_cycle_count(char *s);
void print_array(uint8_t*, int);
void print_now(const char*);
void print_int(int);
void print_time();
void print_error(const char*, int);
uint32_t get_time();


/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RTC_PREDIV_A ((1<<(15-RTC_N_PREDIV_S))-1)
#define RTC_N_PREDIV_S 10
#define RTC_PREDIV_S ((1<<RTC_N_PREDIV_S)-1)
#define BatExt_CS_Pin GPIO_PIN_8
#define BatExt_CS_GPIO_Port GPIOB
#define BatExt_CD_Pin GPIO_PIN_0
#define BatExt_CD_GPIO_Port GPIOA
#define BatExt_PWR_Pin GPIO_PIN_4
#define BatExt_PWR_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define Button1_Pin GPIO_PIN_6
#define Button1_GPIO_Port GPIOA
#define Button1_EXTI_IRQn EXTI9_5_IRQn
#define Button2_Pin GPIO_PIN_7
#define Button2_GPIO_Port GPIOA
#define Button2_EXTI_IRQn EXTI9_5_IRQn
#define BatExt_gain1_Pin GPIO_PIN_10
#define BatExt_gain1_GPIO_Port GPIOA
#define BatExt_gain2_Pin GPIO_PIN_11
#define BatExt_gain2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define VERBOSE					1
#define LPUART_ACTIVE			1
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
