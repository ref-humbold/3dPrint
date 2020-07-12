#include "parser.hpp"
#include <algorithm>

using namespace std::string_literals;

#pragma region gcode_parser

void gcode_parser::parse()
{
    std::string line = reader.get_line();

    for(int i = 1; line != "\0"s; ++i)
    {
        if(line.size() > 0)
        {
            gcode_instruction gcode = parse_line(line, i);

            gcode_instructions.push_back(gcode);
        }

        line = reader.get_line();
    }
}

std::vector<std::string> gcode_parser::split(const std::string & line,
                                             const std::string & delimiters)
{
    std::vector<std::string> result;
    size_t begin_pos = 0;
    size_t end_pos = line.find_first_of(delimiters, begin_pos);

    while(end_pos != std::string::npos)
    {
        if(end_pos != begin_pos)
            result.push_back(line.substr(begin_pos, end_pos - begin_pos));

        begin_pos = end_pos + 1;
        end_pos = line.find_first_of(delimiters, begin_pos);
    }

    if(begin_pos < line.size())
        result.push_back(line.substr(begin_pos, end_pos));

    return result;
}

gcode_instruction gcode_parser::parse_line(const std::string & line, size_t line_number)
{
    gcode_instruction instruction(line_number);
    std::vector<std::string> split_line = split(line, " \t");

    std::for_each(split_line.begin(), split_line.end(), [&](const std::string & arg) {
        instruction.add_argument(arg.at(0), std::stoi(arg.substr(1)));
    });
    return instruction;
}

#pragma endregion
#pragma region printer_parser

void printer_parser::parse()
{
    vec position = start_position;

    for(auto && instr : gcode_instructions)
    {
        std::vector<printer_instruction> printer = convert(instr, position);

        position = vec(printer.back().end_pos);
        std::copy(printer.begin(), printer.end(), std::back_inserter(printer_instructions));
    }
}

printer_parser::arc_type printer_parser::extract_arc_type(const gcode_instruction & instruction)
{
    if(instruction.get_argument_at('G') == 2)
        return instruction.get_argument_at('R') >= 0 ? arc_type::ClockwiseRightSide
                                                     : arc_type::ClockwiseLeftSide;

    return instruction.get_argument_at('R') >= 0 ? arc_type::CounterClockwiseLeftSide
                                                 : arc_type::CounterClockwiseRightSide;
}

vec printer_parser::count_middle(const vec & start, const vec & end, double radius, arc_type type)
{
    vec path_centre = (start + end) / 2;
    vec middle_axis;

    switch(type)
    {
        case arc_type::ClockwiseLeftSide:
        case arc_type::CounterClockwiseLeftSide:
            middle_axis = vec(-path_centre.y, path_centre.x);
            break;

        case arc_type::ClockwiseRightSide:
        case arc_type::CounterClockwiseRightSide:
            middle_axis = vec(path_centre.y, path_centre.x);
            break;
    }

    double required_length =
            sqrt(radius - path_centre.length()) * sqrt(radius + path_centre.length());

    middle_axis *= required_length / path_centre.length();
    return path_centre + middle_axis;
}

std::vector<printer_instruction> printer_parser::convert(const gcode_instruction & instruction,
                                                         const vec & start)
{
    std::vector<printer_instruction> print_instructions;
    vec end(instruction.get_argument_at('X'), instruction.get_argument_at('Y'));

    if(start == end)
        return print_instructions;

    switch(instruction.get_argument_at('G'))
    {
        case 0:
        case 1:
        {
            printer_instruction instr(std::to_string(instruction.get_line_number()), start);

            std::for_each(
                    instruction.begin(), instruction.end(),
                    [&](const std::pair<char, int> argument) { instr.add_argument(argument); });
            print_instructions.push_back(instr);
            break;
        }

        case 2:
        case 3:
        {
            auto generate_id = [&](int line_number, double radians) {
                return std::to_string(line_number) + "_" + std::to_string(radians * 180 / Pi);
            };
            double radius = std::abs(instruction.get_argument_at('R'));
            arc_type type = extract_arc_type(instruction);
            vec middle = count_middle(start, end, radius, type);
            double start_angle = std::acos((start - middle).x / radius);
            double end_angle = std::acos((end - middle).x / radius);

            switch(type)
            {
                case arc_type::ClockwiseLeftSide:
                case arc_type::ClockwiseRightSide:
                {
                    vec previous_point = start;
                    int next_angle = (std::ceil(start_angle / AngleStep) - 1) * AngleStep;

                    end_angle = end_angle > start_angle ? end_angle - 2 * Pi : end_angle;

                    while(next_angle > end_angle)
                    {
                        vec next_point =
                                vec(radius * std::cos(next_angle), radius * std::sin(next_angle));

                        print_instructions.push_back(
                                move_on_arc(generate_id(instruction.get_line_number(), next_angle),
                                            previous_point, grid(next_point)));
                        previous_point = next_point;
                        next_angle -= AngleStep;
                    }

                    print_instructions.push_back(
                            move_on_arc(generate_id(instruction.get_line_number(), end_angle),
                                        previous_point, grid(end)));
                    break;
                }

                case arc_type::CounterClockwiseLeftSide:
                case arc_type::CounterClockwiseRightSide:
                {
                    vec previous_point = start;
                    int next_angle = (std::floor(start_angle / AngleStep) + 1) * AngleStep;

                    end_angle = end_angle < start_angle ? end_angle + 2 * Pi : end_angle;

                    while(next_angle < end_angle)
                    {
                        vec next_point =
                                vec(radius * std::cos(next_angle), radius * std::sin(next_angle));

                        print_instructions.push_back(
                                move_on_arc(std::to_string(instruction.get_line_number()) + "_"
                                                    + std::to_string(next_angle),
                                            previous_point, grid(next_point)));
                        previous_point = next_point;
                        next_angle += AngleStep;
                    }

                    print_instructions.push_back(
                            move_on_arc(std::to_string(instruction.get_line_number()) + "_"
                                                + std::to_string(end_angle),
                                        previous_point, grid(end)));
                    break;
                }
            }

            break;
        }

        default:
            break;
    }

    return print_instructions;
}

printer_instruction printer_parser::move_on_arc(const std::string & identifier,
                                                const vec & previous_point, const grid & next_point)
{
    printer_instruction instr(identifier, previous_point);

    instr.add_argument(std::make_pair('G', 1));
    instr.add_argument(std::make_pair('X', next_point.x));
    instr.add_argument(std::make_pair('Y', next_point.y));
    return instr;
}

#pragma endregion
