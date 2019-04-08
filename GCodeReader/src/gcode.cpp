#include <cstdlib>
#include <iostream>
#include "parameters.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);
    uart_ctrl u(params.port());

    u.send_8(params.ack());
    u.receive_expect_8(params.ack());
    u.send_8(params.stx());
    u.receive_expect_8(0);

    return 0;
}
