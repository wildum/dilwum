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
    friend Vec operator- (const Vec& c1, const Vec& c2);
    friend bool operator!= (const Vec& c1, const Vec& c2);
    friend std::ostream& operator<< (std::ostream& outs, const Vec& c2);

    float x, y;

    inline float length() const
    {
        return sqrt((x*x) + (y*y));
    }

    inline bool notNull() const
    {
        return x != 0 || y != 0;
    }

    inline void normalize()
    {
        if (notNull())
        {
            float len = length();
            x = x / len;
            y = y / len;
        }
    }

    inline float dist(const Vec& v)
    {
        return sqrt(squaredDist(v));
    }

    inline float squaredDist(const Vec& v)
    {
        return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
    }

    inline static Vec lerp(const Vec& v0, const Vec& v1, float t)
    {
        return {v0.x + t * (v1.x - v0.x), v0.y + t * (v1.y - v0.y)};
    }

    void clip()
    {
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (x > config::MAP_WIDTH)
            x = config::MAP_WIDTH;
        if (y > config::MAP_HEIGHT)
            y = config::MAP_HEIGHT;
    }
};

#endif