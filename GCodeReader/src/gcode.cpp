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
    uart_ctrl uart(params.port());

    instruction_list list = parse(params.file(0));
    auto iterator = list.iter();

    uart.send(Connect);
    uart.expect_receive(Connect);

    while(!iterator.empty())
    {
        auto msg = iterator->to_message();

        uart.send(BeginTransmit);
        uart.send(static_cast<uint16_t>(msg.size()));

        for(auto m : msg)
            uart.send(m);

        uart.send(EndTransmit);
        uart.expect_receive(Acknowledge);

        uint16_t data_received = uart.receive();

        if(data_received != msg.size())
            std::cerr << "Sent " << msg.size() << "frames, printer received " << data_received
                      << "\n";

        ++iterator;
    }

    return 0;
}
