#include "uart_ctrl.hpp"

using namespace std::string_literals;

void uart_ctrl::send_8(uint8_t data)
{
    uint8_t sent_data[1] = {data};
    ssize_t res = write(device, sent_data, 1);

    if(res < 0)
        throw uart_error("WRITE ERROR: "s + strerror(errno));
}

uint8_t uart_ctrl::receive_8()
{
    uint8_t recv_data[1] = {0xFF};
    ssize_t res = read(device, recv_data, 1);

    if(res < 0)
        throw uart_error("READ ERROR: "s + strerror(errno));

    return recv_data[0];
}

void uart_ctrl::expect_receive_8(uint8_t expected)
{
    do
    {
        uint8_t data = receive_8();

        if(data == expected)
            break;

        std::cerr << "Expected receive " << hex(expected) << ", got " << hex(data) << "\n";
    } while(true);
}

void uart_ctrl::send_16(uint16_t data)
{
    uint8_t sent_data[2] = {data >> 8, data & 0x00FF};
    ssize_t res = write(device, sent_data, 2);

    if(res < 0)
        throw uart_error("WRITE ERROR: "s + strerror(errno));
}

uint16_t uart_ctrl::receive_16()
{
    uint8_t recv_data[2] = {0xFF, 0xFF};
    ssize_t res = read(device, recv_data, 2);

    if(res < 0)
        throw uart_error("READ ERROR: "s + strerror(errno));

    return (recv_data[0] << 8) | recv_data[1];
}

std::string hex(uint8_t value)
{
    std::stringstream stream;

    stream << std::hex << static_cast<int>(value);

    return stream.str();
}
