#include "factory.h"
#include "randomGen.h"
#include "config.h"
#include "tools.h"

size_t Factory::idCounter = 0;

Food Factory::createRandomFood()
{
    int x = RandomGen::getRandomInt(0, config::MAP_WIDTH);
    int y = RandomGen::getRandomInt(0, config::MAP_HEIGHT);
    int value = RandomGen::getRandomInt(config::FOOD_VALUE_MIN, config::FOOD_VALUE_MAX);
    return {{x, y}, value, idCounter++};
}

Creature Factory::createRandomCreature()
{
    int x = RandomGen::getRandomInt(0, config::MAP_WIDTH);
    int y = RandomGen::getRandomInt(0, config::MAP_HEIGHT);
    int angle = RandomGen::getRandomInt(0, 360);
    return {{x, y}, angle, idCounter++};
}

Creature Factory::createCreature(const std::vector<uint32_t>& dna)
{
    int x = RandomGen::getRandomInt(0, config::MAP_WIDTH);
    int y = RandomGen::getRandomInt(0, config::MAP_HEIGHT);
    int angle = RandomGen::getRandomInt(0, 360);
    return {{x, y}, angle, idCounter++, dna};
}