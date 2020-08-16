#include <cstdlib>
#include <iostream>
#include <vector>
#include "messaging.hpp"
#include "parameters.hpp"
#include "parser.hpp"
#include "uart_ctrl.hpp"

using namespace std::string_literals;

int main(int argc, char * argv[])
{
    parameters params(argc, argv);
    uart_ctrl uart(params.port());
    gcode_parser gcode_p(params.file());

    gcode_p.parse();

    printer_parser printer_p(gcode_p.get_instructions());

    printer_p.parse();
    start_connection(uart);

    for(auto && instr : printer_p.get_instructions())
        send_message(uart, instr);

    return 0;
}
