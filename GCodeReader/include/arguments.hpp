#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <unistd.h>

class args_exception : public std::logic_error
{
public:
    explicit args_exception(const std::string & s) : std::logic_error(s)
    {
    }
};

class arguments
{
public:
    arguments(int argc, char * argv[]) : args{"/dev/ttyACM0", "\x6", "\x15", "\x2", "\x3"}
    {
        parse(argc, argv);
    }

    ~arguments() = default;

    std::string port()
    {
        return args[0];
    }

    uint8_t ack()
    {
        return static_cast<uint8_t>(args[1].front());
    }

    uint8_t nak()
    {
        return static_cast<uint8_t>(args[2].front());
    }

    uint8_t stx()
    {
        return static_cast<uint8_t>(args[3].front());
    }

    uint8_t etx()
    {
        return static_cast<uint8_t>(args[4].front());
    }

private:
    void parse(int argc, char * argv[]);
    void validate(const std::string & value, char option);

    std::vector<std::string> args;
};
