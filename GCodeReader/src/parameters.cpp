#include "parameters.hpp"

using namespace std::string_literals;

void parameters::parse(int argc, char * argv[])
{
    const std::string optstring = ":P:"s;
    int option = getopt(argc, argv, optstring.c_str());

    opterr = 0;

    while(option != -1)
    {
        switch(option)
        {
            case 'P':
                dev_port = optarg;
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

    if(dev_port == "")
        throw params_exception("Missing option -P, no port specified"s);

    for(int i = optind; i < argc; ++i)
    {
        std::string arg = std::string(argv[i]);

        check_gcode(arg);
        files.push_back(arg);
    }
}

void parameters::check_gcode(const std::string & value)
{
    if(value.substr(value.size() - 6, value.size()) != ".gcode"s)
        throw params_exception("Expected *.gcode file, got "s + value);
}
