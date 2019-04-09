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
    parameters(int argc, char * argv[]) : params{"/dev/ttyACM0"}, files{}
    {
        parse(argc, argv);
    }

    ~parameters() = default;

    std::string port()
    {
        return params[0];
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
    void check_gcode(const std::string & value);

    std::vector<std::string> params;
    std::vector<std::string> files;
};
