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
    instruction_list list = parse(params.file());
    auto iterator = list.iter();

    uart.send(Connect);
    uart.expect_receive(Connect);

    while(!iterator.empty())
    {
        auto message = iterator->to_message();

        uart.expect_receive(DataExpected);
        uart.send(BeginTransmit);
        uart.send(static_cast<uint16_t>(message.size()));

        for(auto m : message)
            uart.send(m);

        uart.send(EndTransmit);

        uint16_t data_received = uart.receive();

        if(data_received != message.size())
            std::cerr << "Sent " << message.size() << "frames, printer received " << data_received
                      << "\n";

        uart.expect_receive(Acknowledge);

        ++iterator;
    }

    return 0;
}
