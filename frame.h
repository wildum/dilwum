#ifndef FRAME
#define FRAME

#include "food.h"
#include "creature.h"
#include <vector>

struct Frame
{
    std::vector<FrameFood> food;
    std::vector<FrameCreature> creatures;
};

#endif