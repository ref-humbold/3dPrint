#ifndef MESSAGING_HPP_
#define MESSAGING_HPP_

#include <cstdlib>
#include "instruction.hpp"
#include "usart_ctrl.hpp"

void start_connection(const usart_ctrl & uart);

void send_message(const usart_ctrl & uart, const printer_instruction & instr);

#endif
