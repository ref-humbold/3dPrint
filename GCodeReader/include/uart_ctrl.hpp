#ifndef _USART_HPP_
#define _USART_HPP_

#include <cstdlib>
#include <cerrno>
#include <cinttypes>
#include <cstring>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

enum uart_code : uint16_t
{
    Acknowledge = 0xA000,
    BeginTransmit = 0xB000,
    Connect = 0xC000,
    DataExpected = 0xD000,
    EndTransmit = 0xE000,
    Failure = 0xF000
};

class uart_error : public std::runtime_error
{
public:
    explicit uart_error(const std::string & s) : std::runtime_error(s)
    {
    }
};

class uart_ctrl
{
public:
    explicit uart_ctrl(const std::string & port) : device{open(port.c_str(), O_RDWR | O_NOCTTY)}
    {
    }

    ~uart_ctrl()
    {
        close(device);
    }

    uart_ctrl(const uart_ctrl &) = delete;
    uart_ctrl(uart_ctrl &&) = default;
    uart_ctrl & operator=(const uart_ctrl &) = delete;
    uart_ctrl & operator=(uart_ctrl &&) = default;

    void send(uint16_t data);
    uint16_t receive();
    void expect_receive(uint16_t expected);
    void assert_receive(uint16_t expected);

private:
    int device;
};

std::string hex(uint16_t value);

#endif
