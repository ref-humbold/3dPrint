#include "parser.hpp"
#include <algorithm>

using namespace std::string_literals;

void parser::parse()
{
    std::string line = reader.get_line();

    for(int i = 1; line != "\0"s; ++i)
    {
        if(line.size() > 0)
        {
            gcode_instruction gcode = parse_line(line, i);

            gcode_instructions.push_back(gcode);
        }

        line = reader.get_line();
    }

    point position;

    for(const auto & instr : gcode_instructions)
    {
        std::vector<printer_instruction> printer = convert(instr, position);

        position = printer.back().end_pos;
        std::copy(printer.begin(), printer.end(), std::back_inserter(printer_instructions));
    }
}

std::vector<std::string> parser::split(const std::string & line, const std::string & delimiters)
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

gcode_instruction parser::parse_line(const std::string & line, size_t line_number)
{
    gcode_instruction instruction(line_number);
    std::vector<std::string> split_line = split(line, " \t");

    std::for_each(split_line.begin(), split_line.end(), [&](const std::string & arg) {
        instruction.add_argument(arg.at(0), std::stoi(arg.substr(1)));
    });
    return instruction;
}

std::vector<printer_instruction> parser::convert(const gcode_instruction & instruction,
                                                 const point & start)
{
    std::vector<printer_instruction> instructions;

    switch(instruction.get_argument_at('G'))
    {
        case 0:
        case 1:
        {
            printer_instruction instr(std::to_string(instruction.get_line_number()), start);

            std::for_each(
                    instruction.begin(), instruction.end(),
                    [&](const std::pair<char, int> argument) { instr.add_argument(argument); });
            instructions.push_back(instr);
            break;
        }

        case 2:
        case 3:
        {
            std::pair<uint16_t, uint16_t> middle;
        }

        default:
            break;
    }

    return instructions;
}
