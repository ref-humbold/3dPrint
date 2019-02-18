#include "usart_ctrl.hpp"

using namespace std::string_literals;

uint8_t usart_ctrl::receive8()
{
    uint8_t recv_data[1] = {255};
    ssize_t res = read(device, recv_data, 1);

    if(res < 0)
        throw std::runtime_error("READ ERROR: "s + strerror(errno));

    std::cout << ">->-> " << res << " byte(s) read | value " << std::to_string(recv_data[0])
              << "\n";

    return recv_data[0];
}

uint16_t usart_ctrl::receive16()
{
    uint16_t dataH = receive8();
    uint16_t dataL = receive8();

    return (dataH << 8) | dataL;
}

void usart_ctrl::send8(uint8_t data)
{
    uint8_t sent_data[1] = {data};
    ssize_t res = write(device, sent_data, 1);

    if(res < 0)
        throw std::runtime_error("WRITE ERROR: "s + strerror(errno));

    std::cout << "<-<-< " << res << " byte(s) written | value " << std::to_string(sent_data[0])
              << "\n";
}

void usart_ctrl::send16(uint16_t data)
{
    uint8_t dataH = data >> 8;
    uint8_t dataL = data & 0x00FF;

    send8(dataH);
    send8(dataL);
}
