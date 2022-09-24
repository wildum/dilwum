#include "factory.h"
#include "randomGen.h"
#include "config/config.h"
#include "tools.h"

size_t Factory::idCounter = 0;

Food Factory::createRandomFood()
{
    int x = RandomGen::getRandomInt(0, Config::getMAP_WIDTH());
    int y = RandomGen::getRandomInt(0, Config::getMAP_HEIGHT());
    int value = RandomGen::getRandomInt(Config::getFOOD_VALUE_MIN(), Config::getFOOD_VALUE_MAX());
    return {{x, y}, value, idCounter++};
}

Creature Factory::createRandomCreature()
{
    int x = RandomGen::getRandomInt(0, Config::getMAP_WIDTH());
    int y = RandomGen::getRandomInt(0, Config::getMAP_HEIGHT());
    int angle = RandomGen::getRandomInt(0, 360);
    return {{x, y}, angle, idCounter++};
}

Creature Factory::createCreature(const std::vector<uint32_t>& dna)
{
    int x = RandomGen::getRandomInt(0, Config::getMAP_WIDTH());
    int y = RandomGen::getRandomInt(0, Config::getMAP_HEIGHT());
    int angle = RandomGen::getRandomInt(0, 360);
    return {{x, y}, angle, idCounter++, dna};
}