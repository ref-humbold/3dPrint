#include "vec.hpp"

bool operator==(const grid & g1, const grid & g2)
{
    return g1.x == g2.x && g1.y == g2.y;
}

bool operator!=(const grid & g1, const grid & g2)
{
    return !(g1 == g2);
}

void vec::operator+=(const vec & v)
{
    this->x += v.x;
    this->y += v.y;
}

void vec::operator-=(const vec & v)
{
    this->x -= v.x;
    this->y -= v.y;
}

void vec::operator*=(double c)
{
    this->x *= c;
    this->y *= c;
}

void vec::operator/=(double c)
{
    this->x /= c;
    this->y /= c;
}

vec operator-(vec v)
{
    v.x = -v.x;
    v.y = -v.y;

    return v;
}

vec operator+(vec v1, const vec & v2)
{
    v1 += v2;

    return v1;
}

vec operator-(vec v1, const vec & v2)
{
    v1 -= v2;

    return v1;
}

vec operator*(vec v, double c)
{
    v *= c;

    return v;
}

vec operator*(double c, vec v)
{
    return v * c;
}

vec operator/(vec v, double c)
{
    v /= c;

    return v;
}

vec operator/(double c, vec v)
{
    return v / c;
}

bool operator==(const vec & v1, const vec & v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const vec & v1, const vec & v2)
{
    return !(v1 == v2);
}
