#include <cstdlib>
#include <iostream>
#include "parameters.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);
    uart_ctrl u(params.port());

    u.send_8(ack);
    u.receive_expect_8(ack);
    u.send_8(begin);
    u.receive_expect_8(fail);

    return 0;
}
