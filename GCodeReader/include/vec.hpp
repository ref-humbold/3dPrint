#ifndef VEC_HPP_
#define VEC_HPP_

#include <cstdlib>
#include <cmath>

struct vec
{
public:
    vec() : x{0}, y{0}
    {
    }

    vec(double x, double y) : x{x}, y{y}
    {
    }

    double length() const
    {
        return hypot(x, y);
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
