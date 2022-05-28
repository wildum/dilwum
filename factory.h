#ifndef FACTORY
#define FACTORY

#include "food.h"
#include "creature.h"

class Factory
{
public:
    static Food createRandomFood();
    static Creature createRandomCreatures();
private:
    static size_t idCounter;
};

#endif