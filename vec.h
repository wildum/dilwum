#ifndef VEC
#define VEC

#include <math.h>
#include "tools.h"

#include <boost/serialization/vector.hpp>
#include <boost/serialization/access.hpp>

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

    inline void scale(float s)
    {
        x *= s;
        y *= s;
    }

    inline float dist(const Vec& v)
    {
        return sqrt(squaredDist(v));
    }

    inline float squaredDist(const Vec& v) const
    {
        return (v.x - x) * (v.x - x) + (v.y - y) * (v.y - y);
    }

    inline static Vec lerp(const Vec& v0, const Vec& v1, float t)
    {
        return {v0.x + t * (v1.x - v0.x), v0.y + t * (v1.y - v0.y)};
    }

    void clip(uint16_t radius)
    {
        if (x < radius)
            x = radius;
        if (y < radius)
            y = radius;
        if (x > Config::getMAP_WIDTH()-radius)
            x = Config::getMAP_WIDTH()-radius;
        if (y > Config::getMAP_HEIGHT()-radius)
            y = Config::getMAP_HEIGHT()-radius;
    }

    const bool isOut() const
    {
        return x <= 0 || x >= Config::getMAP_WIDTH() || y <= 0 || y > Config::getMAP_HEIGHT();
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
};

#endif