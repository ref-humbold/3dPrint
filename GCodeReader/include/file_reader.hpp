#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <string>

class file_exception : public std::runtime_error
{
public:
    explicit file_exception(const std::string & s) : std::runtime_error(s)
    {
    }
};

class file_reader
{
public:
    explicit file_reader(const std::string & filename) : desc{fopen(filename.c_str(), "r")}
    {
        if(desc == nullptr)
            throw file_exception(strerror(errno));
    }

    ~file_reader()
    {
        fclose(desc);
    }

    file_reader(const file_reader &) = delete;
    file_reader(file_reader &&) noexcept;
    file_reader & operator=(const file_reader &) = delete;
    file_reader & operator=(file_reader &&) noexcept;

    std::string get_line();

    static const size_t MAX_LINE_LENGTH = 128;

private:
    FILE * desc;

    std::string trim(std::string line);
};

#endif
