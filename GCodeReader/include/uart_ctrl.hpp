#ifndef _USART_HPP_
#define _USART_HPP_

#include <cstdlib>
#include <cerrno>
#include <cinttypes>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

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

    void send_8(uint8_t data);
    uint8_t receive_8();
    void receive_expect_8(uint8_t expected);

private:
    int device;
};

#endif
