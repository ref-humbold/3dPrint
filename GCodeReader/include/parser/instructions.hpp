#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_

#include <cstdlib>
#include <cmath>
#include <map>
#include <string>
#include <vector>

struct vec
{
public:
    vec() : x{0}, y{0}
    {
    }

    vec(int x, int y) : x{x}, y{y}
    {
    }

    double length()
    {
        return hypot(x, y);
    }

    int x;
    int y;
};

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
    explicit instruction(const std::map<char, int> & m)
        : from_point{vec()}, to_point{from_point}, next{nullptr}
    {
        for(const auto & c : m)
            if(c.first == 'G' || c.first == 'M')
                type = c;
            else
                args.insert(c);

        if(args.find('X') != args.end() && args.find('Y') != args.end())
            to_point = vec(args.at('X'), args.at('Y'));
    }

    std::string get_type()
    {
        return std::string(type.first, 1) + std::to_string(type.second);
    }

    std::vector<uint16_t> to_message();

    vec from_point;
    vec to_point;
    instruction * next;

protected:
    std::pair<char, int> type;
    std::map<char, int, comparator> args;
};

class circle_instruction : public instruction
{
public:
    explicit circle_instruction(const std::map<char, int> & m) : instruction(m)
    {
        vec middle = count_middle();

        args.emplace('I', middle.x);
        args.emplace('J', middle.y);
    }

private:
    vec count_middle();
};

class instruction_list
{
public:
    using node_t = instruction *;

    instruction_list() : begin_list{nullptr}, end_list{nullptr}
    {
    }

    void add(const std::map<char, int> & m);

private:
    node_t begin_list;
    node_t end_list;

    instruction * instruction_factory(const std::map<char, int> & m);
};

#endif
