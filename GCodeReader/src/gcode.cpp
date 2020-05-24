#include <cstdlib>
#include <iostream>
#include "parameters.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);
    uart_ctrl uart(params.port());

    return 0;
}
