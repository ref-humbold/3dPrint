#include "parser.hpp"

std::vector<std::string> split(const std::string & line, const std::string & delimiters)
{
    std::vector<std::string> result;
    size_t begin_pos = 0;
    size_t end_pos = line.find_first_of(delimiters, begin_pos);

    while(end_pos != std::string::npos)
    {
        if(end_pos != begin_pos)
            result.push_back(line.substr(begin_pos, end_pos - begin_pos));

        begin_pos = end_pos + 1;
        end_pos = line.find_first_of(delimiters, begin_pos);
    }

    if(begin_pos < line.size())
        result.push_back(line.substr(begin_pos, end_pos));

    return result;
}

gcode_instruction parse_line(const std::string & line, size_t line_number)
{
    gcode_instruction instruction(line_number);
    std::vector<std::string> split_line = split(line, " \t");

    for(const auto & arg : split_line)
        instruction.add_argument(arg.at(0), std::stoi(arg.substr(1)));

    return instruction;
}

std::vector<printer_instruction> convert(const gcode_instruction & instruction)
{
    std::vector<printer_instruction> instructions;

    return instructions;
}
