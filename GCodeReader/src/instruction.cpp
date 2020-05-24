#include "instruction.hpp"

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

std::vector<uint16_t> instruction::get_message()
{
    std::vector<uint16_t> message;

    for(const auto & arg : arguments)
    {
        message.push_back(static_cast<uint16_t>(arg.first));
        message.push_back(static_cast<uint16_t>(arg.second));
    }

    return message;
}

void instruction::add_argument(char code, int value)
{
    arguments.emplace(code, value);
}

instruction parse_line(const std::string & line)
{
    instruction instr;
    std::vector<std::string> split_line = split(line, " \t");

    if(split_line.at(0) == "G0" || split_line.at(0) == "G1")
        for(const auto & arg : split_line)
            instr.add_argument(arg.at(0), std::stoi(arg.substr(1)));
    else if(split_line.at(0) == "G2" || split_line.at(0) == "G3")
    {
    }
}
