#ifndef USART_HPP_
#define USART_HPP_

#include <cerrno>
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

enum usart_code : uint16_t
{
    Acknowledge = 0xA000,
    BeginTransmit = 0xB000,
    Connect = 0xC000,
    DataExpected = 0xD000,
    EndTransmit = 0xE000,
    Failure = 0xF000
};

class usart_error : public std::runtime_error
{
public:
    explicit usart_error(const std::string & s) : std::runtime_error(s)
    {
    }
};

class failure_message : public std::runtime_error
{
public:
    failure_message() : std::runtime_error("Received 'Failure' message")
    {
    }
};

class usart_ctrl
{
public:
    explicit usart_ctrl(const std::string & port) : device{open(port.c_str(), O_RDWR | O_NOCTTY)}
    {
    }

    ~usart_ctrl()
    {
        close(device);
    }

    usart_ctrl(const usart_ctrl &) = delete;
    usart_ctrl(usart_ctrl &&) = default;
    usart_ctrl & operator=(const usart_ctrl &) = delete;
    usart_ctrl & operator=(usart_ctrl &&) = default;

    void send(uint16_t data) const;
    uint16_t receive() const;
    void expect_receive(uint16_t expected) const;
    void assert_receive(uint16_t expected) const;

private:
    int device;
};

std::string hex(uint16_t value);

#endif
