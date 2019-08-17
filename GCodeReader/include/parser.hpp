#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>
#include "file_reader.hpp"
#include "instruction_list.hpp"

std::vector<std::string> split(const std::string & s, const std::string & delimiters);

std::string prefix(const std::string & s, char delimiter);

instruction_list parse(const std::string & filename);

#endif
