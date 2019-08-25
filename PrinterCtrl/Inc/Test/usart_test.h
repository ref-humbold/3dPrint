#ifndef __usart_test_H
#define __usart_test_H

#include "gpio.h"
#include "main.h"
#include "usart.h"

void usart_test()
{
    uint16_t data;

    uart_send(&huart2, Connect);
    uart_expect_receive(&huart2, Connect);
    uart_receive(&huart2, &data);
    uart_send(&huart2, data);
    uart_send(&huart2, Acknowledge);
    uart_assert_receive(&huart2, Acknowledge);
};

#endif
