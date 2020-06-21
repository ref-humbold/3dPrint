#include "instruction.hpp"

void printer_instruction::add_argument(const std::pair<char, int> & argument)
{
    if(argument.first == 'X')
        end_pos.x = static_cast<uint8_t>(argument.second);

    if(argument.first == 'Y')
        end_pos.y = static_cast<uint8_t>(argument.second);

    message.push_back((static_cast<uint16_t>(argument.first) << 8)
                      | static_cast<uint16_t>(argument.second));
}

std::ostream & operator<<(std::ostream & os, const gcode_instruction & instruction)
{
    os << "[: " << instruction.get_line_number() << " / ";

    for(const auto & arg : instruction)
        os << arg.first << arg.second << " ";

    os << ":]";
    return os;
}

std::ostream & operator<<(std::ostream & os, const printer_instruction & instruction)
{
    os << "{: " << instruction.get_identifier() << " / ";

    for(const auto & arg : instruction)
        os << std::hex << arg << " ";

    os << ":}";
    return os;
}
