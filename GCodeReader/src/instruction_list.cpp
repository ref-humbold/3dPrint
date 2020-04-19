#include "instruction_list.hpp"

void instruction_list::add(const std::map<char, int> & arguments)
{
    if(begin_list != nullptr && end_list == nullptr)
        return;

    if(begin_list == nullptr)
    {
        auto * instr = instruction_factory(arguments, vec(0, 0));

        begin_list = instr;
        end_list = begin_list;
    }
    else
    {
        auto * instr = instruction_factory(arguments, end_list->to_point);

        end_list->next = instr;
        end_list = end_list->next;
    }
}

std::ostream & operator<<(std::ostream & os, const instruction_list & list)
{
    auto it = list.iter();

    os << "[|";

    if(!it.empty())
    {
        os << " " << *it;
        ++it;
    }

    while(!it.empty())
    {
        os << ", " << *it;
        ++it;
    }

    os << " |]";

    return os;
}
