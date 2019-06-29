#include <cstdlib>
#include <iostream>
#include "parameters.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);

    std::cout << params.port() << "\n";

    uart_ctrl u(params.port());

    u.send(Conn);
    u.expect_receive(Conn);
    u.send(Ack);

    while(true)
    {
        std::cout << hex(u.receive()) << "\n";
    }

    return 0;
}
