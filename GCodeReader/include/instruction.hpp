#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <cstdlib>
#include <cinttypes>
#include <map>
#include <string>
#include <vector>

class instruction
{
public:
    instruction()
    {
    }

    std::vector<uint16_t> get_message();
    void add_argument(char code, int value);

private:
    std::map<char, int> arguments;
};

instruction parse_line(const std::string & line);

#endif
