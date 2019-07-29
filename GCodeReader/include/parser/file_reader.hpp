#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <string>

class file_reader
{
public:
    explicit file_reader(const std::string & filename) : desc{fopen(filename.c_str(), "r")}
    {
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
};

#endif
