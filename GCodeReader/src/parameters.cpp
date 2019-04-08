#include "parameters.hpp"

using namespace std::string_literals;

void parameters::parse(int argc, char * argv[])
{
    const std::string optstring = ":P:a:n:s:e:"s;
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 'P':
                params[0] = optarg;
                break;

            case 'a':
                params[1] = optarg;
                validate(params[1], 'a');
                break;

            case 'n':
                params[2] = optarg;
                validate(params[2], 'n');
                break;

            case 's':
                params[3] = optarg;
                validate(params[3], 's');
                break;

            case 'e':
                params[4] = optarg;
                validate(params[4], 'e');
                break;

            case '?':
                throw params_exception("Unknown option -"s + static_cast<char>(optopt));

            case ':':
                throw params_exception("Option -"s + static_cast<char>(optopt)
                                       + " requires an argument"s);

            default:
                break;
        }

        option = getopt(argc, argv, optstring.c_str());
    }
}

void parameters::validate(const std::string & value, char option)
{
    if(value.size() != 1)
        throw params_exception("Option "s + option + " expected a single character, but "s
                               + std::to_string(value.size()) + " characters given"s);
}
