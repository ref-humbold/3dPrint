/**
 ******************************************************************************
 * File Name          : USART.h
 * Description        : This file provides code for the configuration
 *                      of the USART instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdlib.h>
    /* USER CODE END Includes */

    extern UART_HandleTypeDef huart2;

    /* USER CODE BEGIN Private defines */
    extern HAL_StatusTypeDef uart_status;

    enum uart_code
    {
        ack = 0xA0,
        begin = 0xB0,
        conn = 0xC0,
        end = 0xE0,
        fail = 0xF0
    };
    /* USER CODE END Private defines */

    void MX_USART2_UART_Init(void);

    /* USER CODE BEGIN Prototypes */
    void HAL_UART_TxCpltCallback(UART_HandleTypeDef * huart);
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);
    void uart_send_8(UART_HandleTypeDef * huart, uint8_t data);
    void uart_receive_8(UART_HandleTypeDef * huart, uint8_t * data);
    void uart_expect_receive_8(UART_HandleTypeDef * huart, uint8_t expected);
    /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
