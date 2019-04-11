#include "uart_ctrl.hpp"

using namespace std::string_literals;

void uart_ctrl::send_8(uint8_t data)
{
    uint8_t sent_data[1] = {data};
    ssize_t res = write(device, sent_data, 1);

    if(res < 0)
        throw uart_error("WRITE ERROR: "s + strerror(errno));
}

void uart_ctrl::send_repeat_8(uint8_t data)
{
    uint8_t rec;

    do
    {
        send_8(data);
        rec = receive_8();
    } while(rec != ack);
}

uint8_t uart_ctrl::receive_8()
{
    uint8_t recv_data[1] = {0xFF};
    ssize_t res = read(device, recv_data, 1);

    if(res < 0)
        throw uart_error("READ ERROR: "s + strerror(errno));

    return recv_data[0];
}

void uart_ctrl::receive_expect_8(uint8_t expected)
{
    uint8_t data = receive_8();

    if(data != expected)
        throw uart_error("Expected "s + std::to_string(static_cast<int>(expected))
                         + " from UART, got "s + std::to_string(static_cast<int>(data)));
}
