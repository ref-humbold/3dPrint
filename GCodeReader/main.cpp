#include <cstdlib>
#include <iostream>
#include "usart_ctrl.hpp"

int main()
{
    usart_ctrl u("/dev/ttyACM0");

    while(true)
    {
        u.send8(65);
        std::cout << "## " << u.receive8() << "\n";
    }

    return 0;
}
