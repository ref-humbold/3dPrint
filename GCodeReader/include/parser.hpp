#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>
#include "file_reader.hpp"
#include "instruction.hpp"

class parser
{
public:
    explicit parser(const std::string & filename) : reader{file_reader(filename)}
    {
    }

    std::vector<gcode_instruction> get_gcode_instructions()
    {
        return gcode_instructions;
    }

    std::vector<printer_instruction> get_printer_instructions()
    {
        return printer_instructions;
    }

    void parse();

private:
    std::vector<std::string> split(const std::string & line, const std::string & delimiters);
    gcode_instruction parse_line(const std::string & line, size_t line_number);
    std::vector<printer_instruction> convert(const gcode_instruction & instruction,
                                             const point & start);

    file_reader reader;
    std::vector<gcode_instruction> gcode_instructions;
    std::vector<printer_instruction> printer_instructions;
};

#endif
