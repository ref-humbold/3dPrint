#include "vec.hpp"

void vec::operator+=(const vec & v)
{
    this->x += v.x;
    this->y += v.y;
}

void vec::operator*=(double c)
{
    this->x *= c;
    this->y *= c;
}

vec operator+(vec v1, const vec & v2)
{
    v1 += v2;

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

bool operator==(const vec & v1, const vec & v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const vec & v1, const vec & v2)
{
    return !(v1 == v2);
}
