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
    parameters(int argc, char * argv[]) : params{"/dev/ttyACM0", "\x6", "\x15", "\x2", "\x3"}
    {
        parse(argc, argv);
    }

    ~parameters() = default;

    std::string port()
    {
        return params[0];
    }

    uint8_t ack()
    {
        return static_cast<uint8_t>(params[1].front());
    }

    uint8_t nak()
    {
        return static_cast<uint8_t>(params[2].front());
    }

    uint8_t stx()
    {
        return static_cast<uint8_t>(params[3].front());
    }

    uint8_t etx()
    {
        return static_cast<uint8_t>(params[4].front());
    }

private:
    void parse(int argc, char * argv[]);
    void validate(const std::string & value, char option);

    std::vector<std::string> params;
};
