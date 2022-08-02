#ifndef TOOLS
#define TOOLS

#include <iostream>
#include "config.h"
#include <math.h>

namespace tools
{
    template<typename T>
    inline void log(const T& message)
    {
        std::cerr << message << std::endl;
    }

    inline bool floatCompare(float a, float b)
    {
        return fabs(a-b) < config::EPSILON;
    }

    template<typename T>
    inline float lerp(T a, T b, float t)
    {
        return a + t * (b - a);
    }

    inline float degreesToRadian(float degrees)
    {
        return degrees * M_PI / 180;
    }
}

#endif