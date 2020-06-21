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
    enum class arc_type
    {
        ClockwiseLeft,
        ClockwiseRight,
        CounterClockwiseLeft,
        CounterClockwiseRight
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
    arc_type extract_arc_type(const gcode_instruction & instruction);
    std::vector<std::string> split(const std::string & line, const std::string & delimiters);
    gcode_instruction parse_line(const std::string & line, size_t line_number);
    vec count_middle(const vec & start, const vec & end, double radius, arc_type type);
    std::vector<printer_instruction> convert(const gcode_instruction & instruction,
                                             const vec & start);

    const double Pi = atan2(0, -1);
    const int AngleStep = 5;
    file_reader reader;
    std::vector<gcode_instruction> gcode_instructions;
    std::vector<printer_instruction> printer_instructions;
};

#endif
