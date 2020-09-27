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
                port_ = optarg;
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

    if(argc > optind)
        file_ = std::string(argv[optind]);
}

void parameters::validate()
{
    if(port_.empty())
        throw params_exception("Missing option -P, no port specified"s);

    if(file_ == "")
        throw params_exception("No *.gcode files specified"s);

    if(file_.substr(file_.size() - 6, file_.size()) != ".gcode"s)
        throw params_exception("Expected *.gcode file, got "s + file_);
}

std::ostream & operator<<(std::ostream & os, const parameters & p)
{
    os << "Parameters { ";
    os << "Port: " << p.port() << ", ";
    os << "File: " << p.file();
    os << " }";
    return os;
}
