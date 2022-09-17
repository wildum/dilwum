#ifndef FACTORY
#define FACTORY

#include "food.h"
#include "creature.h"

class Factory
{
public:
    static Food createRandomFood();
    static Creature createRandomCreature();
    static Creature createCreature(const std::vector<uint32_t>& dna);
private:
    static size_t idCounter;
};

#endif