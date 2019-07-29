#include <cstdlib>
#include <iostream>
#include "parameters.hpp"
#include "parser/parser.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);

    std::cout << params.port() << " -- " << params.file(0) << "\n";

    instruction_list list = parse(params.file(0));

    std::cout << list << "\n";

    return 0;
}
