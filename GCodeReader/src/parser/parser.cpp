#include "parser/parser.hpp"

std::vector<std::string> split(const std::string & s, const std::string & delimiters)
{
    std::vector<std::string> result;
    size_t begin_pos = 0;
    size_t end_pos = s.find_first_of(delimiters, begin_pos);

    while(end_pos != std::string::npos)
    {
        if(end_pos != begin_pos)
            result.push_back(s.substr(begin_pos, end_pos - begin_pos));

        begin_pos = end_pos + 1;
        end_pos = s.find_first_of(delimiters, begin_pos);
    }

    if(begin_pos < s.size())
        result.push_back(s.substr(begin_pos, end_pos));

    return result;
}

std::string prefix(const std::string & s, char delimiter)
{
    return s.substr(0, s.find(delimiter));
}

instruction_list parse(const std::string & filename)
{
    instruction_list list;
    file_reader reader(filename);

    while(true)
    {
        std::string line = reader.get_line();

        if(line.at(0) == '\0')
            break;

        line = prefix(line, ';');

        std::vector<std::string> args = split(line, " \t\r\n");
        std::map<char, int> args_map;

        for(const auto & a : args)
            args_map.emplace(a.at(0), std::stoi(a.substr(1)));

        list.add(args_map);
    }

    return list;
}
