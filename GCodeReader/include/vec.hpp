#ifndef VEC_HPP_
#define VEC_HPP_

#include <cstdlib>
#include <cinttypes>
#include <cmath>
#include <iostream>
#include <utility>

#pragma region vec

struct vec
{
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

    double x, y;
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
std::ostream & operator<<(std::ostream & os, const vec & v);

#pragma endregion
#pragma region grid

struct grid
{
    grid() : x{0}, y{0}
    {
    }

    grid(uint8_t x, uint8_t y) : x{x}, y{y}
    {
    }

    explicit grid(const vec & v)
        : x{static_cast<uint8_t>(round(v.x))}, y{static_cast<uint8_t>(round(v.y))}
    {
    }

    operator vec()
    {
        return vec(x, y);
    }

    uint8_t x, y;
};

bool operator==(const grid & g1, const grid & g2);
bool operator!=(const grid & g1, const grid & g2);
std::ostream & operator<<(std::ostream & os, const grid & g);

#pragma endregion

#endif
