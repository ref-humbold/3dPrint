#include "instruction.hpp"

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

void instruction::add_argument(char code, size_t value)
{
    arguments.push_back(std::make_pair(code, value));
}

std::vector<std::string> split(const std::string & line)
{
    std::vector<std::string> split_line;

    return split_line;
}
