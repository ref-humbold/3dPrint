#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstdlib>
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string & s, const std::string & delimiter);
std::string prefix(const std::string & s, const std::string & delimiter);

#endif
