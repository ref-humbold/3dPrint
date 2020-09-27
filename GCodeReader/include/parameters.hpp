#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <cstdlib>
#include <exception>
#include <iostream>
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
    parameters(int argc, char * argv[]) : port_{""}, file_{""}
    {
        parse(argc, argv);
        validate();
    }

    const std::string & port() const
    {
        return port_;
    }

    const std::string & file() const
    {
        return file_;
    }

private:
    void parse(int argc, char * argv[]);
    void validate();

    std::string port_;
    std::string file_;
};

std::ostream & operator<<(std::ostream & os, const parameters & p);

#endif
