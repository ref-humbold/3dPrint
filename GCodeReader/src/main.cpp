#include <cstdlib>
#include <iostream>
#include "uart_ctrl.hpp"

using namespace std::string_literals;

const uint8_t ACK = static_cast<uint8_t>('A');

int main(int argc, char * argv[])
{
    uart_ctrl u("/dev/ttyACM0"s);
    uint8_t data;

    while(true)
    {
        u.send_8(ACK);
        data = u.recv_8();
        std::cout << "## " << data << "\n";
    }

    return 0;
}
