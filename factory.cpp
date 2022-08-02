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

Creature Factory::createRandomCreatures()
{
    int x = RandomGen::getRandomInt(0, config::MAP_WIDTH);
    int y = RandomGen::getRandomInt(0, config::MAP_HEIGHT);
    int angle = RandomGen::getRandomInt(0, 360);
    return {{x, y}, angle, idCounter++};
}