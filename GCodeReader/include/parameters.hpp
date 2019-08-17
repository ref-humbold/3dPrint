#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>

class params_exception : public std::logic_error
{
public:
    explicit params_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

class parameters
{
public:
    parameters(int argc, char * argv[]) : dev_port{""}, files{}
    {
        parse(argc, argv);
    }

    ~parameters() = default;

    std::string port()
    {
        return dev_port;
    }

    std::string file(size_t i)
    {
        return files.at(i);
    }

    std::vector<std::string>::const_iterator files_begin()
    {
        return files.cbegin();
    }

    std::vector<std::string>::const_iterator files_end()
    {
        return files.cend();
    }

private:
    void parse(int argc, char * argv[]);

    std::string dev_port;
    std::vector<std::string> files;
};
