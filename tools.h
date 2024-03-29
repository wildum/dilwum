#ifndef TOOLS
#define TOOLS

#include <iostream>
#include "config/config.h"
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
        return fabs(a-b) < Config::getEPSILON();
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

    inline float radianToDegrees(float radians)
    {
        return radians * 180 / M_PI;
    }

    inline int map(float value, float oldMax, float newMax)
    {
        return std::max((int) round((value * (newMax + 1) / oldMax) - 0.500001), 0);
    }

    inline float squaredDist(int x1, int y1, int x2, int y2)
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    inline float dist(int x1, int y1, int x2, int y2)
    {
        return sqrt(squaredDist(x1, y1, x2, y2));
    }

    inline void pause()
    {
        tools::log("Press enter to continue...");
        std::cin.get(); // wait for user to continue
    }
}

#endif