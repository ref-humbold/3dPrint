#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <cstdlib>
#include <cinttypes>
#include <iostream>
#include <map>
#include <vector>
#include "vec.hpp"

class gcode_instruction
{
public:
    explicit gcode_instruction(size_t line_number) : line_number{line_number}
    {
    }

    size_t get_line_number() const
    {
        return line_number;
    }

    int get_argument_at(char code) const
    {
        return arguments.at(code);
    }

    std::map<char, int>::const_iterator begin() const
    {
        return arguments.cbegin();
    }

    std::map<char, int>::const_iterator end() const
    {
        return arguments.cend();
    }

    void add_argument(char code, int value)
    {
        arguments.emplace(code, value);
    }

private:
    size_t line_number;
    std::map<char, int> arguments;
};

class printer_instruction
{
public:
    explicit printer_instruction(const std::string & identifier, vec start_pos)
        : start_pos{start_pos.to_grid()}, identifier{identifier}
    {
    }

    const std::string & get_identifier() const
    {
        return identifier;
    }

    std::vector<uint16_t>::const_iterator begin() const
    {
        return message.cbegin();
    }

    std::vector<uint16_t>::const_iterator end() const
    {
        return message.cend();
    }

    void add_argument(const std::pair<char, int> & argument);

    grid start_pos;
    grid end_pos;

private:
    std::string identifier;
    std::vector<uint16_t> message;
};

std::ostream & operator<<(std::ostream & os, const gcode_instruction & instruction);

std::ostream & operator<<(std::ostream & os, const printer_instruction & instruction);

#endif
