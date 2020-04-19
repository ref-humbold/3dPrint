#ifndef __usart_test_H
#define __usart_test_H

#include "gpio.h"
#include "main.h"
#include "usart.h"

void usart_1_test()
{
    uart_assert_receive(&huart2, Connect);
    uart_send(&huart2, Connect);
};

void usart_2_test()
{
    uint16_t data;

    uart_assert_receive(&huart2, BeginTransmit);
    uart_receive(&huart2, &data);
    uart_assert_receive(&huart2, EndTransmit);
    uart_send(&huart2, 0x1);
    uart_send(&huart2, data);
    uart_send(&huart2, Acknowledge);
}

void usart_3_test()
{
    uart_assert_receive(&huart2, Acknowledge);
}

#endif
