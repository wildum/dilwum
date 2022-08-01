#include "factory.h"
#include "randomGen.h"
#include "config.h"

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
    int dir_x = RandomGen::getRandomInt(0, config::MAP_WIDTH);
    int dir_y = RandomGen::getRandomInt(0, config::MAP_HEIGHT);
    Vec dir{dir_x, dir_y};
    dir.normalize();
    return {{x, y}, dir, idCounter++};
}