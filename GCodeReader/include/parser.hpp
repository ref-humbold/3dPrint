#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>
#include "file_reader.hpp"
#include "instruction.hpp"
#include "vec.hpp"

class parser
{
private:
    enum class middle_place
    {
        Left,
        Right
    };

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
    middle_place extract_middle_place(const gcode_instruction & instruction);
    std::vector<std::string> split(const std::string & line, const std::string & delimiters);
    gcode_instruction parse_line(const std::string & line, size_t line_number);
    vec count_middle(const gcode_instruction & instruction, const vec & start);
    std::vector<printer_instruction> convert(const gcode_instruction & instruction,
                                             const vec & start);

    file_reader reader;
    std::vector<gcode_instruction> gcode_instructions;
    std::vector<printer_instruction> printer_instructions;
};

#endif
