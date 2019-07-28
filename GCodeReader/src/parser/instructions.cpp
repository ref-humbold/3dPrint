#include "parser/instructions.hpp"

// region instruction

std::vector<uint16_t> instruction::to_message()
{
    std::vector<uint16_t> message;

    message.push_back(static_cast<uint16_t>(type.first) | static_cast<uint8_t>(type.first));

    for(const auto & p : args)
        message.push_back(static_cast<uint16_t>(p.first) | static_cast<uint8_t>(p.first));

    return message;
}

// endregion
// region circle_instruction

vec circle_instruction::count_middle()
{
}

// endregion
// region instruction_list

void instruction_list::add(const std::map<char, int> & m)
{
    auto * instr = instruction_factory(m);

    if(begin_list != nullptr && end_list == nullptr)
        return;

    if(begin_list == nullptr)
    {
        begin_list = instr;
        end_list = begin_list;
    }
    else
    {
        instr->from_point = end_list->to_point;
        end_list->next = instr;
    }

    end_list = end_list->next;

    if(end_list->get_type() == "M30")
    {
        end_list->next = begin_list;
        end_list = nullptr;
    }
}

instruction * instruction_list::instruction_factory(const std::map<char, int> & m)
{
    auto argG = m.find('G');

    if(argG != m.end() && (argG->second == 2 || argG->second == 3))
        return new circle_instruction(m);

    return new instruction(m);
}

// endregion
