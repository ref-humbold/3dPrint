#include "instructions.hpp"
#include <algorithm>

// region instruction

std::vector<uint16_t> instruction::to_message() const
{
    std::vector<uint16_t> message;

    message.push_back((type.first << 8U) | type.second);

    std::transform(arguments.begin(), arguments.end(), std::back_inserter(message),
                   [](auto argument) {
                       return (argument.first << 8U) | static_cast<uint8_t>(argument.second);
                   });

    return message;
}

std::ostream & operator<<(std::ostream & os, const instruction & instr)
{
    os << "{ " << static_cast<char>(instr.type.first) << instr.type.second;

    for(const auto & a : instr.arguments)
        os << " " << static_cast<char>(a.first) << a.second;

    os << " }";

    return os;
}

// endregion
// region circle_instruction

circle_instruction::middle_direction circle_instruction::get_direction()
{
    if(type.second == 2)
        return arguments.at(static_cast<uint16_t>('R')) >= 0 ? middle_direction::Right
                                                             : middle_direction::Left;

    return arguments.at(static_cast<uint16_t>('R')) >= 0 ? middle_direction::Left
                                                         : middle_direction::Right;
}

vec circle_instruction::count_middle()
{
    uint16_t radius = static_cast<uint16_t>('R');

    if(from_point == to_point)
        return from_point;

    vec path_centre = (from_point + to_point) / 2;
    vec middle_axis;

    switch(get_direction())
    {
        case middle_direction::Left:
            middle_axis = vec(-path_centre.y, path_centre.x);
            break;

        case middle_direction::Right:
            middle_axis = vec(path_centre.y, path_centre.x);
            break;
    }

    double required_length = sqrt(arguments.at(radius) - path_centre.length())
                             * sqrt(arguments.at(radius) + path_centre.length());
    middle_axis *= required_length / path_centre.length();
    arguments[radius] = std::abs(arguments.at(radius));

    return path_centre + middle_axis;
}

// endregion

instruction * instruction_factory(const std::map<char, int> & arguments, const vec & from)
{
    auto argG = arguments.find('G');

    if(argG != arguments.end() && (argG->second == 2 || argG->second == 3))
        return new circle_instruction(arguments, from);

    return new instruction(arguments, from);
}

// endregion
