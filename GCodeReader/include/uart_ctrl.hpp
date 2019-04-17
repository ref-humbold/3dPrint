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

enum uart_code : uint8_t
{
    ack = 0xA0,
    begin = 0xB0,
    conn = 0xC0,
    end = 0xE0,
    fail = 0xF0
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

    void send_8(uint8_t data);
    uint8_t receive_8();
    void expect_receive_8(uint8_t expected);

private:
    int device;
};

std::string hex(uint8_t value);

#endif
