#include <cstdlib>
#include <iostream>
#include <vector>
#include "messaging.hpp"
#include "parameters.hpp"
#include "parser.hpp"
#include "usart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);
    usart_ctrl uart(params.port());
    gcode_parser gcode_p(params.file());

    std::cerr << params << "\n";
    gcode_p.parse();

    std::cerr << "Parsing...\n";
    printer_parser printer_p(gcode_p.instructions());

    printer_p.parse();

    std::cerr << "UART connect...\n";
    start_connection(uart);

    for(auto && instr : printer_p.instructions())
        send_message(uart, instr);

    return 0;
}
