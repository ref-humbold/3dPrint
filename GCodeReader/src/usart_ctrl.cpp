#include "usart_ctrl.hpp"

using namespace std::string_literals;

void usart_ctrl::send(uint16_t data) const
{
    uint8_t sent_data[2] = {static_cast<uint8_t>(data >> 8U), static_cast<uint8_t>(data & 0x00FFU)};
    ssize_t res = write(device, sent_data, 2);

    if(res < 0)
        throw usart_error("WRITE ERROR: "s + strerror(errno));
}

uint16_t usart_ctrl::receive() const
{
    uint8_t recv_data[2] = {0xFF, 0xFF};
    ssize_t res = read(device, recv_data, 2);

    if(res < 0)
        throw usart_error("READ ERROR: "s + strerror(errno));

    uint16_t data = static_cast<uint16_t>(static_cast<uint16_t>(recv_data[0]) << 8U)
                    | static_cast<uint16_t>(recv_data[1]);

    if(data == Failure)
        throw failure_message();

    return data;
}

void usart_ctrl::expect_receive(uint16_t expected) const
{
    do
    {
        uint16_t data = receive();

        if(data == expected)
            break;

        std::cerr << "Expected receive " << hex(expected) << ", got " << hex(data) << "\n";
    } while(true);
}

void usart_ctrl::assert_receive(uint16_t expected) const
{
    uint16_t data = receive();

    if(data != expected)
        throw usart_error("Expected receive "s + hex(expected) + ", got "s + hex(data));
}

std::string hex(uint16_t value)
{
    std::stringstream stream;

    stream << std::hex << static_cast<int>(value) << std::dec;
    return stream.str();
}
