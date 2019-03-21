#include <cstdlib>
#include <iostream>
#include "uart_ctrl.hpp"

using namespace std::string_literals;

const char ACK = 'A';
const char NAK = 'N';
const char STX = 'S';
const char FF = 'F';

int main(int argc, char * argv[])
{
    uart_ctrl uart("/dev/ttyACM0"s);

    while(true)
    {
        uart.send_8(ACK);

        if(uart.recv_8() != ACK)
            throw std::runtime_error("ACK not received");

        uart.send_8(STX);

        if(uart.recv_8() != FF)
            throw std::runtime_error("FF not received");
    }

    return 0;
}
