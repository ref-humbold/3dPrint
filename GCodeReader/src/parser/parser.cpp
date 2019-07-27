#include "parser/parser.hpp"

std::vector<std::string> split(const std::string & s, const std::string & delimiter)
{
    std::vector<std::string> result;
    size_t begin_pos = 0;

    while(begin_pos != std::string::npos)
    {
        size_t end_pos = s.find(delimiter, begin_pos);

        result.push_back(s.substr(begin_pos, end_pos - begin_pos));
        begin_pos = end_pos + delimiter.size();
    }

    return result;
}

std::string prefix(const std::string & s, const std::string & delimiter)
{
    return s.substr(s.find(delimiter));
}
