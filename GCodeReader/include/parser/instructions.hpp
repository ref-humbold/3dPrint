#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "vec.hpp"

struct comparator
{
    bool operator()(char c1, char c2)
    {
        if(c1 == 'X')
            return true;

        if(c2 == 'X')
            return false;

        if(c1 == 'Y')
            return true;

        if(c2 == 'Y')
            return false;

        return c1 < c2;
    }
};

class instruction
{
public:
    explicit instruction(const std::map<char, int> & m, const vec & from)
        : from_point{from}, to_point{from}, next{nullptr}
    {
        for(const auto & c : m)
            if(c.first == 'G' || c.first == 'M')
                type = c;
            else
                args.insert(c);

        if(m.find('X') != m.end() && m.find('Y') != m.end())
            to_point = vec(m.at('X'), m.at('Y'));
    }

    std::string get_type() const
    {
        return std::string(type.first, 1) + std::to_string(type.second);
    }

    std::vector<uint16_t> to_message() const;

    friend std::ostream & operator<<(std::ostream & os, const instruction & instr);

    vec from_point;
    vec to_point;
    instruction * next;

protected:
    std::pair<char, int> type;
    std::map<char, int, comparator> args;
};

std::ostream & operator<<(std::ostream & os, const instruction & instr);

class circle_instruction : public instruction
{
public:
    explicit circle_instruction(const std::map<char, int> & m, const vec & from)
        : instruction(m, from)
    {
        vec middle = count_middle();

        args.emplace('I', round(middle.x));
        args.emplace('J', round(middle.y));
    }

private:
    vec count_middle();
};

class instruction_runner
{
public:
    explicit instruction_runner(instruction * elem) : current{elem}
    {
    }

    ~instruction_runner() = default;
    instruction_runner(const instruction_runner & it) = default;
    instruction_runner(instruction_runner && it) noexcept = default;
    instruction_runner & operator=(const instruction_runner & it) = default;
    instruction_runner & operator=(instruction_runner && it) noexcept = default;

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

    instruction_runner & operator++()
    {
        if(!empty())
            current = current->next;

        return *this;
    }

protected:
    const instruction * current;
};

class instruction_iterator : public instruction_runner
{
public:
    explicit instruction_iterator(instruction * elem) : instruction_runner(elem)
    {
    }

    ~instruction_iterator() = default;
    instruction_iterator(const instruction_iterator & it) = default;
    instruction_iterator(instruction_iterator && it) noexcept = default;
    instruction_iterator & operator=(const instruction_iterator & it) = default;
    instruction_iterator & operator=(instruction_iterator && it) noexcept = default;

    bool empty() override
    {
        return current == nullptr || current->get_type() == "M30";
    }
};

class instruction_list
{
public:
    instruction_list() : begin_list{nullptr}, end_list{nullptr}
    {
    }

    instruction_runner run() const
    {
        return instruction_runner(begin_list);
    }

    instruction_iterator iter() const
    {
        return instruction_iterator(begin_list);
    }

    void add(const std::map<char, int> & m);

    friend std::ostream & operator<<(std::ostream & os, const instruction_list & list);

private:
    instruction * begin_list;
    instruction * end_list;
};

std::ostream & operator<<(std::ostream & os, const instruction_list & list);

instruction * instruction_factory(const std::map<char, int> & m, const vec & from);

#endif
