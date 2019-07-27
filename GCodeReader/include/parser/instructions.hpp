#ifndef INSTRUCTIONS_HPP_
#define INSTRUCTIONS_HPP_

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

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
    explicit instruction(const std::vector<std::pair<char, int>> & v) : next{nullptr}
    {
        for(const auto & c : v)
            if(c.first == 'G' || c.first == 'M')
                type = c;
            else
                args.insert(c);
    }

    std::string get_type()
    {
        return std::string(type.first, 1) + std::to_string(type.second);
    }

    std::vector<uint16_t> to_message();

    instruction * next;

private:
    std::pair<char, int> type;
    std::map<char, int, comparator> args;
};

class instruction_list
{
public:
    using node_t = instruction *;

    instruction_list() : begin_list{nullptr}, end_list{nullptr}
    {
    }

    void add(const std::vector<std::pair<char, int>> & v);

private:
    node_t begin_list;
    node_t end_list;
};

#endif
