#include "file_reader.hpp"

const size_t file_reader::MAX_LINE_LENGTH;

file_reader::file_reader(file_reader && f) noexcept
{
    this->desc = nullptr;
    std::swap(this->desc, f.desc);
}

file_reader & file_reader::operator=(file_reader && f) noexcept
{
    std::swap(this->desc, f.desc);

    return *this;
}

std::string file_reader::get_line()
{
    char line[MAX_LINE_LENGTH];
    char * res = fgets(line, sizeof(line), desc);

    if(res == nullptr && feof(desc))
        return std::string(1, '\0');

    if(res == nullptr && ferror(desc))
        throw std::logic_error(strerror(errno));

    return trim(line);
}

std::string file_reader::trim(std::string line)
{
    std::string chars = " \t\n\r";

    line.erase(std::min(line.size(), line.find_first_of(";")));
    line.erase(0, line.find_first_not_of(chars));
    line.erase(line.find_last_not_of(chars) + 1);
    return line;
}
