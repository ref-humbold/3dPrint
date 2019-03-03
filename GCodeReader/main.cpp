#include <cstdlib>
#include <iostream>
#include "usart_ctrl.hpp"

int main(int argc, char * argv[])
{
    usart_ctrl u("/dev/ttyACM0");

    if(argc < 2)
        throw std::logic_error("No data provided.");

    while(true)
    {
        u.send_8(static_cast<uint8_t>(atoi(argv[1])));
        std::cout << "## " << u.receive_8() << "\n";
    }

    return 0;
}
