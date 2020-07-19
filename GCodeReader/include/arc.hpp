#ifndef ARC_HPP_
#define ARC_HPP_

#include <cmath>
#include "vec.hpp"

enum class arc_type
{
    ClockwiseLeftSide,
    ClockwiseRightSide,
    CounterClockwiseLeftSide,
    CounterClockwiseRightSide
};

class arc
{
public:
    arc(const vec & start_point, const vec & end_point, double radius, arc_type type)
        : start_point_{start_point}, end_point_{end_point}, radius_{radius}, type_{type}
    {
        count_middle();
    }

    const vec & start_point()
    {
        return start_point_;
    }

    const vec & end_point()
    {
        return end_point_;
    }

    double radius()
    {
        return radius_;
    }

    arc_type type()
    {
        return type_;
    }

    vec point(double degrees);
    double degrees(vec point);

    const double Pi = atan2(0, -1);

private:
    void count_middle();

    vec start_point_, end_point_, middle;
    double radius_;
    arc_type type_;
};

#endif
