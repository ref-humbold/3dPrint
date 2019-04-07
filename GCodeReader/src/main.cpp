#include <cstdlib>
#include <iostream>
#include "arguments.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    arguments args(argc, argv);
    uart_ctrl u(args.port());

    while(true)
    {
        uint8_t data;

        u.send_8(args.ack());
        data = u.recv_8();
        std::cout << "## 1 : " << data << "\n";
        data = u.recv_8();
        std::cout << "## 2 : " << data << "\n";
    }

    return 0;
}
