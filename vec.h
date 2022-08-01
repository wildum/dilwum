#ifndef VEC
#define VEC

#include <math.h>

class Vec
{
public:
    Vec() : x(0), y(0){}; 
    Vec(float ix, float iy) : x(ix), y(iy){};
    Vec(int ix, int iy) : x(ix), y(iy){};
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
    void rotateAroundPoint(const Vec& p, int angle)
    {
        float s = sin(angle);
        float c = cos(angle);

        x -= p.x;
        y -= p.y;

        float xnew = x * c - y * s;
        float ynew = x * s + y * c;

        x = xnew + p.x;
        y = ynew + p.y;
    }

    float getAngleWithyAxis() const
    {
        if (!notNull())
            return 0;
        float len = length();
        float angle = acos(y/len) * 180/M_PI;
        return x > 0 ? -angle : angle;
    }

    static Vec lerp(const Vec& v0, const Vec& v1, float t)
    {
        return {v0.x + t * (v1.x - v0.x), v0.y + t * (v1.y - v0.y)};
    }
};

#endif