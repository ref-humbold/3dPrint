#include "arc.hpp"

vec arc::point(double degrees)
{
    vec vec_radius(radius_ * std::cos(degrees / 180.0 * Pi),
                   radius_ * std::sin(degrees / 180.0 * Pi));

    return middle + vec_radius;
}

double arc::degrees(vec point)
{
    vec vec_radius = point - middle;
    double angle = std::atan2(vec_radius.y, vec_radius.x) / Pi * 180.0;

    return angle >= 0 ? angle : angle + 360.0;
}

void arc::count_middle()
{
    vec half_displacement = (end_point_ - start_point_) / 2;
    vec middle_axis;

    switch(type_)
    {
        case arc_type::ClockwiseLeftSide:
        case arc_type::CounterClockwiseLeftSide:
            middle_axis = vec(-half_displacement.y, half_displacement.x);
            break;

        case arc_type::ClockwiseRightSide:
        case arc_type::CounterClockwiseRightSide:
            middle_axis = vec(half_displacement.y, -half_displacement.x);
            break;
    }

    double required_length =
            sqrt(radius_ - half_displacement.length()) * sqrt(radius_ + half_displacement.length());

    middle_axis *= required_length / half_displacement.length();
    middle = start_point_ + half_displacement + middle_axis;
}
