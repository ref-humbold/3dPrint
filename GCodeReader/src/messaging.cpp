#include "messaging.hpp"
#include <string>

using namespace std::string_literals;

void start_connection(const uart_ctrl & uart)
{
    uart.send(Connect);
    uart.assert_receive(Connect);
}

void send_message(const uart_ctrl & uart, const printer_instruction & instr)
{
    uart.send(BeginTransmit);
    uart.send(instr.size());

    for(auto && msg : instr)
        uart.send(msg);

    uart.send(EndTransmit);

    size_t received_size = uart.receive();

    try
    {
        uart.assert_receive(Acknowledge);
    }
    catch(const failure_message &)
    {
        std::cerr << "Sent " << instr.size() << " packs, received " << received_size;
        throw;
    }
}
