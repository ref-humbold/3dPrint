#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_

#include <cstdlib>
#include <cmath>
#include <cstdint>
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
    explicit instruction(const std::map<char, int> & arguments, const vec & from)
        : from_point{from}, to_point{from}, next{nullptr}
    {
        for(const auto & arg : arguments)
            if(arg.first == 'G' || arg.first == 'M')
                type = std::make_pair(static_cast<uint16_t>(arg.first), arg.second);
            else
                args.emplace(static_cast<uint16_t>(arg.first), arg.second);

        if(arguments.find('X') != arguments.end() && arguments.find('Y') != arguments.end())
            to_point = vec(arguments.at('X'), arguments.at('Y'));
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
    std::pair<uint16_t, int> type;
    std::map<uint16_t, int, comparator> args;
};

std::ostream & operator<<(std::ostream & os, const instruction & instr);

class circle_instruction : public instruction
{
public:
    explicit circle_instruction(const std::map<char, int> & arguments, const vec & from)
        : instruction(arguments, from)
    {
        vec middle = count_middle();

        args.emplace(static_cast<uint16_t>('I'), round(middle.x));
        args.emplace(static_cast<uint16_t>('J'), round(middle.y));
    }

private:
    vec count_middle();
};

instruction * instruction_factory(const std::map<char, int> & arguments, const vec & from);

#endif
