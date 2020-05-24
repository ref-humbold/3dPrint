#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_

#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>

class instruction
{
public:
    instruction()
    {
    }

    std::vector<uint16_t> get_message();
    void add_argument(char code, size_t value);

private:
    std::vector<std::pair<char, size_t>> arguments;
};

std::vector<std::string> split(const std::string & line);

#endif
