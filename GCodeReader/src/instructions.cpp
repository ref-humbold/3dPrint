#include "instructions.hpp"

// region instruction

std::vector<uint16_t> instruction::to_message() const
{
    std::vector<uint16_t> message;

    message.push_back(static_cast<uint16_t>(static_cast<uint16_t>(type.first) << 8U)
                      | static_cast<uint8_t>(type.second));

    for(const auto & p : args)
        message.push_back(static_cast<uint16_t>(static_cast<uint16_t>(p.first) << 8U)
                          | static_cast<uint8_t>(p.second));

    return message;
}

std::ostream & operator<<(std::ostream & os, const instruction & instr)
{
    os << "{ " << instr.type.first << instr.type.second;

    for(const auto & a : instr.args)
        os << " " << a.first << a.second;

    os << " }";

    return os;
}

// endregion
// region circle_instruction

vec circle_instruction::count_middle()
{
    if(from_point == to_point)
        return from_point;

    double dl = hypot((from_point.x - to_point.x) / 2, (from_point.y - to_point.y) / 2);
    vec h = (type.second == 2 && args.at('R') >= 0) || (type.second == 3 && args.at('R') < 0)
                    ? vec(-(from_point.y - to_point.y) / 2, (from_point.x - to_point.x) / 2)
                    : vec((from_point.y - to_point.y) / 2, -(from_point.x - to_point.x) / 2);

    h *= (sqrt(args.at('R') - dl) * sqrt(args.at('R') + dl) / dl);
    args['R'] = std::abs(args.at('R'));

    return h + vec((from_point.x + to_point.x) / 2, (from_point.y + to_point.y) / 2);
}

// endregion

instruction * instruction_factory(const std::map<char, int> & m, const vec & from)
{
    auto argG = m.find('G');

    if(argG != m.end() && (argG->second == 2 || argG->second == 3))
        return new circle_instruction(m, from);

    return new instruction(m, from);
}

// endregion
