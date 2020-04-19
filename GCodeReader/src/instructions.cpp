#include "instructions.hpp"

// region instruction

std::vector<uint16_t> instruction::to_message() const
{
    std::vector<uint16_t> message;

    message.push_back((type.first << 8U) | type.second);

    std::transform(args.begin(), args.end(), std::back_inserter(message), [](auto argument) {
        return (argument.first << 8U) | static_cast<uint8_t>(argument.second);
    });

    return message;
}

std::ostream & operator<<(std::ostream & os, const instruction & instr)
{
    os << "{ " << static_cast<char>(instr.type.first) << instr.type.second;

    for(const auto & a : instr.args)
        os << " " << static_cast<char>(a.first) << a.second;

    os << " }";

    return os;
}

// endregion
// region circle_instruction

vec circle_instruction::count_middle()
{
    uint16_t r16 = static_cast<uint16_t>('R');

    if(from_point == to_point)
        return from_point;

    double dl = hypot((from_point.x - to_point.x) / 2, (from_point.y - to_point.y) / 2);
    vec h = (type.second == 2 && args.at(r16) >= 0) || (type.second == 3 && args.at(r16) < 0)
                    ? vec(-(from_point.y - to_point.y) / 2, (from_point.x - to_point.x) / 2)
                    : vec((from_point.y - to_point.y) / 2, -(from_point.x - to_point.x) / 2);

    h *= (sqrt(args.at(r16) - dl) * sqrt(args.at(r16) + dl) / dl);
    args[r16] = std::abs(args.at(r16));

    return h + vec((from_point.x + to_point.x) / 2, (from_point.y + to_point.y) / 2);
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
