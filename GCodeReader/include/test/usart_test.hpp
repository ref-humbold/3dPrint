#ifndef USART_TEST_HPP_
#define USART_TEST_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include "uart_ctrl.hpp"

void usart_test(const std::string & port)
{
    uart_ctrl uart(port);
    uint16_t data = 0x1234;

    std::cout << ">>> TEST 1 :: Connect\n";
    uart.expect_receive(Connect);
    uart.send(Connect);
    std::cout << ">>> TEST 1 :: Done\n";
    std::cout << ">>> TEST 2 :: 0x1234\n";
    uart.send(data);
    uart.assert_receive(data);
    std::cout << ">>> TEST 2 :: Done\n";
    std::cout << ">>> TEST 3 :: Acknowledge & Failure\n";
    uart.assert_receive(Acknowledge);
    uart.send(DataExpect);
    uart.expect_receive(Failure);
    std::cout << ">>> TEST 3 :: Done\n";
};

#endif
