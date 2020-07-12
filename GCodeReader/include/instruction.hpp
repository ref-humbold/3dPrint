#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <cstdlib>
#include <cinttypes>
#include <iostream>
#include <map>
#include <vector>
#include "vec.hpp"

#pragma region gcode_instruction

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

    friend bool operator==(const gcode_instruction & g1, const gcode_instruction & g2);
    friend bool operator!=(const gcode_instruction & g1, const gcode_instruction & g2);

private:
    size_t line_number;
    std::map<char, int> arguments;
};

bool operator==(const gcode_instruction & g1, const gcode_instruction & g2);
bool operator!=(const gcode_instruction & g1, const gcode_instruction & g2);
std::ostream & operator<<(std::ostream & os, const gcode_instruction & instruction);

#pragma endregion
#pragma region gcode_instruction

class printer_instruction
{
public:
    explicit printer_instruction(const std::string & identifier, vec start_pos)
        : start_pos{start_pos}, identifier{identifier}
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

    friend bool operator==(const printer_instruction & p1, const printer_instruction & p2);
    friend bool operator!=(const printer_instruction & p1, const printer_instruction & p2);

    grid start_pos;
    grid end_pos;

private:
    std::string identifier;
    std::vector<uint16_t> message;
};

bool operator==(const printer_instruction & p1, const printer_instruction & p2);
bool operator!=(const printer_instruction & p1, const printer_instruction & p2);
std::ostream & operator<<(std::ostream & os, const printer_instruction & instruction);

#pragma endregion

#endif
