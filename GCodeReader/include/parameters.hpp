#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
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
    parameters(int argc, char * argv[]) : dev_port{""}, filename{""}
    {
        parse(argc, argv);
        validate();
    }

    const std::string & port()
    {
        return dev_port;
    }

    const std::string & file()
    {
        return filename;
    }

private:
    void parse(int argc, char * argv[]);
    void validate();

    std::string dev_port;
    std::string filename;
};

#endif
