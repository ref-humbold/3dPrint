#include "uart_ctrl.hpp"

using namespace std::string_literals;

uint8_t uart_ctrl::recv_8()
{
    uint8_t recv_data[1] = {255};
    ssize_t res = read(device, recv_data, 1);

    if(res < 0)
        throw uart_exception("READ ERROR: "s + strerror(errno));

    return recv_data[0];
}

void uart_ctrl::send_8(uint8_t data)
{
    uint8_t sent_data[1] = {data};
    ssize_t res = write(device, sent_data, 1);

    if(res < 0)
        throw uart_exception("WRITE ERROR: "s + strerror(errno));
}
