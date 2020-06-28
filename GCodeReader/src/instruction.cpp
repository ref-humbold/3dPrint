#include "instruction.hpp"

bool operator==(const gcode_instruction & g1, const gcode_instruction & g2)
{
    return g1.arguments == g2.arguments;
}

bool operator!=(const gcode_instruction & g1, const gcode_instruction & g2)
{
    return !(g1 == g2);
}

std::ostream & operator<<(std::ostream & os, const gcode_instruction & instruction)
{
    os << "[: " << instruction.get_line_number() << " / ";

    for(const auto & arg : instruction)
        os << arg.first << arg.second << " ";

    os << ":]";
    return os;
}

void printer_instruction::add_argument(const std::pair<char, int> & argument)
{
    if(argument.first == 'X')
        end_pos.x = static_cast<uint8_t>(argument.second);

    if(argument.first == 'Y')
        end_pos.y = static_cast<uint8_t>(argument.second);

    message.push_back((static_cast<uint16_t>(argument.first) << 8)
                      | static_cast<uint16_t>(argument.second));
}

bool operator==(const printer_instruction & p1, const printer_instruction & p2)
{
    return p1.start_pos == p2.start_pos && p1.end_pos == p2.end_pos && p1.message == p2.message;
}

bool operator!=(const printer_instruction & p1, const printer_instruction & p2)
{
    return !(p1 == p2);
}

std::ostream & operator<<(std::ostream & os, const printer_instruction & instruction)
{
    os << "{: " << instruction.get_identifier() << " / ";

    for(const auto & arg : instruction)
        os << std::hex << arg << " ";

    os << ":}";
    return os;
}
