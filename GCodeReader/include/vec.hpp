#ifndef VEC_HPP_
#define VEC_HPP_

#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <utility>

struct grid
{
    grid() : x{0}, y{0}
    {
    }

    grid(uint8_t x, uint8_t y) : x{x}, y{y}
    {
    }

    uint8_t x;
    uint8_t y;
};

struct vec
{
    vec() : x{0}, y{0}
    {
    }

    vec(double x, double y) : x{x}, y{y}
    {
    }

    explicit vec(const grid & g) : x{static_cast<double>(g.x)}, y{static_cast<double>(g.y)}
    {
    }

    double length() const
    {
        return hypot(x, y);
    }

    grid to_grid() const
    {
        return grid(static_cast<uint8_t>(round(x)), static_cast<uint8_t>(round(y)));
    }

    void operator+=(const vec & v);
    void operator-=(const vec & v);
    void operator*=(double c);
    void operator/=(double c);

    double x;
    double y;
};

bool operator==(const grid & g1, const grid & g2);
bool operator!=(const grid & g1, const grid & g2);

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
