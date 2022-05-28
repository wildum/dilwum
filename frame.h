#ifndef FRAME
#define FRAME

#include "food.h"
#include "creature.h"
#include <vector>

struct Frame
{
    float t = 0;
    std::vector<FrameFood> food;
    std::vector<FrameCreature> creatures;
};

#endif