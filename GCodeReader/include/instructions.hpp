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

instruction * instruction_factory(const std::map<char, int> & m, const vec & from);

#endif
