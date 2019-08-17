#include <cstdlib>
#include <iostream>
#include "instruction_list.hpp"
#include "parameters.hpp"
#include "parser.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);

    std::cout << params.port() << " -- " << params.file(0) << "\n";

    instruction_list list = parse(params.file(0));
    auto iterator = list.iter();

    std::cout << list << "\n";

    while(!iterator.empty())
    {
        auto msg = iterator->to_message();

        for(auto m : msg)
            std::cout << std::hex << m << " ";

        std::cout << "\n";
        ++iterator;
    }

    return 0;
}
