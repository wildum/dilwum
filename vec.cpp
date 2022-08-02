#include "vec.h"

bool operator== (const Vec& c1, const Vec& c2)
{
    return tools::floatCompare(c1.x, c2.x) && tools::floatCompare(c1.y, c2.y);
}

bool operator!= (const Vec& c1, const Vec& c2)
{
    return !(operator==(c1, c2));
}

std::ostream& operator<< (std::ostream& outs, const Vec& c)
{
    return outs << "(" << c.x << "," << c.y << ")";
}