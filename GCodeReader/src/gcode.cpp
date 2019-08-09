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
    auto runner = list.run();

    std::cout << list << "\n";

    while(!runner.empty())
    {
        auto msg = runner->to_message();

        for(auto m : msg)
            std::cout << std::hex << m << " ";

        std::cout << "\n";
        ++runner;
    }

    return 0;
}
