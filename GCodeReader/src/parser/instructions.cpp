#include "parser/instructions.hpp"

std::vector<uint16_t> instruction::to_message()
{
    std::vector<uint16_t> message;

    message.push_back(static_cast<uint16_t>(type.first) | static_cast<uint8_t>(type.first));

    for(const auto & p : args)
        message.push_back(static_cast<uint16_t>(p.first) | static_cast<uint8_t>(p.first));

    return message;
}

void instruction_list::add(const std::vector<std::pair<char, int>> & v)
{
    auto * instr = new instruction(v);

    if(begin_list != nullptr && end_list == nullptr)
        return;

    if(begin_list == nullptr)
    {
        begin_list = instr;
        end_list = begin_list;
    }
    else
        end_list->next = instr;

    end_list = end_list->next;

    if(end_list->get_type() == "M30")
    {
        end_list->next = begin_list;
        end_list = nullptr;
    }
}
