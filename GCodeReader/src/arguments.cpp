#include "arguments.hpp"

using namespace std::string_literals;

void arguments::parse(int argc, char * argv[])
{
    const std::string optstring = ":P:a:n:s:e:"s;
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 'P':
                args[0] = optarg;
                break;

            case 'a':
                args[1] = optarg;
                validate(args[1], 'a');
                break;

            case 'n':
                args[2] = optarg;
                validate(args[2], 'n');
                break;

            case 's':
                args[3] = optarg;
                validate(args[3], 's');
                break;

            case 'e':
                args[4] = optarg;
                validate(args[4], 'e');
                break;

            case '?':
                throw args_exception("Unknown option -"s + static_cast<char>(optopt));

            case ':':
                throw args_exception("Option -"s + static_cast<char>(optopt)
                                     + " requires an argument"s);

            default:
                break;
        }

        option = getopt(argc, argv, optstring.c_str());
    }
}

void arguments::validate(const std::string & value, char option)
{
    if(value.size() != 1)
        throw args_exception("Option "s + option + " expected a single character, but "s
                             + std::to_string(value.size()) + " characters given"s);
}
