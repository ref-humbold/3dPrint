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

    u.send_8(conn);
    u.expect_receive_8(conn);
    u.send_8(ack);

    while(true)
    {
        std::cout << hex(u.receive_8()) << "\n";
    }

    return 0;
}
