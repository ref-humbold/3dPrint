#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>
#include "arc.hpp"
#include "file_reader.hpp"
#include "instruction.hpp"
#include "vec.hpp"

class gcode_parser
{
public:
    explicit gcode_parser(const std::string & filename) : reader{file_reader(filename)}
    {
    }

    std::vector<gcode_instruction> get_instructions()
    {
        return gcode_instructions;
    }

    void parse();

private:
    std::vector<std::string> split(const std::string & line, const std::string & delimiters);
    gcode_instruction parse_line(const std::string & line, size_t line_number);

    file_reader reader;
    std::vector<gcode_instruction> gcode_instructions;
};

class printer_parser
{
public:
    explicit printer_parser(const std::vector<gcode_instruction> & gcode_instructions,
                            vec start = vec(0, 0))
        : start_position{start}, gcode_instructions{gcode_instructions}
    {
    }

    std::vector<printer_instruction> get_instructions()
    {
        return printer_instructions;
    }

    void parse();

private:
    arc_type extract_arc_type(const gcode_instruction & instruction);
    std::vector<printer_instruction> convert(const gcode_instruction & instruction,
                                             const vec & start);
    printer_instruction move_on_arc(const std::string & identifier, const vec & previous_point,
                                    const grid & next_point);

    const double DegreesStep = 5.0;
    vec start_position;
    std::vector<gcode_instruction> gcode_instructions;
    std::vector<printer_instruction> printer_instructions;
};

#endif
