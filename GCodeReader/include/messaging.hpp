#ifndef MESSAGING_HPP_
#define MESSAGING_HPP_

#include <cstdlib>
#include "instruction.hpp"
#include "uart_ctrl.hpp"

void connect(const uart_ctrl & uart);

void send_message(const uart_ctrl & uart, const printer_instruction & instr);

#endif
