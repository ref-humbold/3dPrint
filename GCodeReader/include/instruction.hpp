#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <cstdlib>
#include <cinttypes>
#include <map>
#include <vector>

class gcode_instruction
{
public:
    explicit gcode_instruction(size_t line_number) : line_number{line_number}
    {
    }

    size_t get_line_number()
    {
        return line_number;
    }

    int get_argument_at(char code)
    {
        return arguments.at(code);
    }

    std::map<char, int>::const_iterator cbegin()
    {
        return arguments.cbegin();
    }

    std::map<char, int>::const_iterator cend()
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
    explicit printer_instruction(const std::string & identifier) : identifier{identifier}
    {
    }

    const std::string & get_identifier()
    {
        return identifier;
    }

    std::vector<uint16_t>::const_iterator cbegin()
    {
        return message.cbegin();
    }

    std::vector<uint16_t>::const_iterator cend()
    {
        return message.cend();
    }

    void add_argument(std::pair<char, int> argument)
    {
        message.push_back(static_cast<uint16_t>(argument.first));
        message.push_back(static_cast<uint16_t>(argument.second));
    }

private:
    std::string identifier;
    std::vector<uint16_t> message;
};

#endif
