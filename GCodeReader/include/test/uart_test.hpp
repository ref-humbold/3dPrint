#ifndef USART_TEST_HPP_
#define USART_TEST_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include "uart_ctrl.hpp"

void uart_1_test(const std::string & port)
{
    uart_ctrl uart(port);

    uart.send(Connect);
    uart.assert_receive(Connect);
};

void uart_2_test(const std::string & port)
{
    uart_ctrl uart(port);
    uint16_t data = 0x1234;

    uart.send(BeginTransmit);
    uart.send(data);
    uart.send(EndTransmit);
    uart.assert_receive(0x1);
    uart.assert_receive(data);
    uart.assert_receive(Acknowledge);
};

void uart_3_test(const std::string & port)
{
    uart_ctrl uart(port);

    uart.send(DataExpected);
    uart.assert_receive(Failure);
};

#endif
