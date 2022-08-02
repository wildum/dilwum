#ifndef VEC
#define VEC

#include <math.h>
#include "tools.h"

class Vec
{
public:
    Vec() : x(0), y(0){}; 
    Vec(float ix, float iy) : x(ix), y(iy){};
    Vec(int ix, int iy) : x(ix), y(iy){};

    friend bool operator== (const Vec& c1, const Vec& c2);
    friend bool operator!= (const Vec& c1, const Vec& c2);
    friend std::ostream& operator<< (std::ostream& outs, const Vec& c2);

    float x, y;
    float length() const
    {
        return sqrt((x*x) + (y*y));
    }
    bool notNull() const
    {
        return x != 0 || y != 0;
    }
    void normalize()
    {
        if (notNull())
        {
            float len = length();
            x = x / len;
            y = y / len;
        }
    }

    static Vec lerp(const Vec& v0, const Vec& v1, float t)
    {
        return {v0.x + t * (v1.x - v0.x), v0.y + t * (v1.y - v0.y)};
    }
};

#endif