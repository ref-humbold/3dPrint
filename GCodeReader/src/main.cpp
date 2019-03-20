#include <cstdlib>
#include <iostream>
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    uart_ctrl u("/dev/ttyACM0"s);

    if(argc < 2)
        throw std::logic_error("No data provided.");

    while(true)
    {
        u.send_8(static_cast<uint8_t>(atoi(argv[1])));
        std::cout << "## " << u.receive_8() << "\n";
    }

    return 0;
}
