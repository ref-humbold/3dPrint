#ifndef VEC_HPP_
#define VEC_HPP_

#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <utility>

struct vec
{
    vec() : x{0}, y{0}
    {
    }

    vec(double x, double y) : x{x}, y{y}
    {
    }

    explicit vec(const std::pair<double, double> & pair) : x{pair.first}, y{pair.second}
    {
    }

    double length() const
    {
        return hypot(x, y);
    }

    std::pair<uint16_t, uint16_t> grid() const
    {
        return std::make_pair(static_cast<uint16_t>(round(x)), static_cast<uint16_t>(round(y)));
    }

    void operator+=(const vec & v);
    void operator-=(const vec & v);
    void operator*=(double c);
    void operator/=(double c);

    double x;
    double y;
};

vec operator-(vec v);
vec operator+(vec v1, const vec & v2);
vec operator-(vec v1, const vec & v2);
vec operator*(vec v, double c);
vec operator*(double c, vec v);
vec operator/(vec v, double c);
vec operator/(double c, vec v);
bool operator==(const vec & v1, const vec & v2);
bool operator!=(const vec & v1, const vec & v2);

#endif
