#ifndef __usart_test_H
#define __usart_test_H

#include "gpio.h"
#include "main.h"
#include "usart.h"

void usart_1_test()
{
    usart_assert_receive(&huart2, Connect);
    usart_send(&huart2, Connect);
};

void usart_2_test()
{
    uint16_t data;

    usart_assert_receive(&huart2, BeginTransmit);
    usart_receive(&huart2, &data);
    usart_assert_receive(&huart2, EndTransmit);
    usart_send(&huart2, 0x1);
    usart_send(&huart2, data);
    usart_send(&huart2, Acknowledge);
}

void usart_3_test()
{
    usart_assert_receive(&huart2, Acknowledge);
}

#endif
