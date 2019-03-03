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

class usart_ctrl
{
public:
    explicit usart_ctrl(const std::string & port) : usart_ctrl(port.c_str())
    {
    }

    explicit usart_ctrl(const char * port) : device{open(port, O_RDWR | O_NOCTTY)}
    {
    }

    ~usart_ctrl()
    {
        close(device);
    }

    uint8_t receive_8();
    uint16_t receive_16();
    void send_8(uint8_t data);
    void send_16(uint16_t data);

private:
    int device;
};

#endif
