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

class uart_exception : std::runtime_error
{
public:
    explicit uart_exception(const std::string & arg) : std::runtime_error(arg)
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

    uint8_t recv_8();
    void send_8(uint8_t data);

private:
    int device;
};

#endif
