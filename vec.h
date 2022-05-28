#ifndef VEC
#define VEC

#include <math.h>

class Vec
{
public:
    Vec() : x(0), y(0){}; 
    Vec(float ix, float iy) : x(ix), y(iy){};
    float x, y;
    float length()
    {
        return sqrt((x*x) + (y*y));
    }
    void normalize()
    {
        float len = length();
        x = x / len;
        y = y / len;
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
};

#endif