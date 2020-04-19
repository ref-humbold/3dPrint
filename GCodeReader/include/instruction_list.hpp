#ifndef INSTRUCTION_LIST_HPP_
#define INSTRUCTION_LIST_HPP_

#include <cstdlib>
#include <iostream>
#include <map>
#include "instructions.hpp"

class instruction_iterator
{
public:
    explicit instruction_iterator(instruction * elem) : current{elem}
    {
    }

    ~instruction_iterator() = default;
    instruction_iterator(const instruction_iterator & it) = default;
    instruction_iterator(instruction_iterator && it) noexcept = default;
    instruction_iterator & operator=(const instruction_iterator & it) = default;
    instruction_iterator & operator=(instruction_iterator && it) noexcept = default;

    virtual bool empty()
    {
        return current == nullptr;
    }

    const instruction & operator*() const
    {
        return *current;
    }

    const instruction * operator->() const
    {
        return &(operator*());
    }

    instruction_iterator & operator++()
    {
        if(!empty())
            current = current->next;

        return *this;
    }

protected:
    const instruction * current;
};

class instruction_list
{
public:
    instruction_list() : begin_list{nullptr}, end_list{nullptr}
    {
    }

    instruction_iterator iter() const
    {
        return instruction_iterator(begin_list);
    }

    void add(const std::map<char, int> & arguments);

    friend std::ostream & operator<<(std::ostream & os, const instruction_list & list);

private:
    instruction * begin_list;
    instruction * end_list;
};

std::ostream & operator<<(std::ostream & os, const instruction_list & list);

#endif
