#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>
#include "instruction.hpp"

gcode_instruction parse_line(const std::string & line, size_t line_number);

std::vector<printer_instruction> convert(const gcode_instruction & instruction);

#endif
