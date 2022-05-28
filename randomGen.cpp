#include "randomGen.h"


void RandomGen::initialize()
{
    gen = std::mt19937{rd()};
}
int RandomGen::getRandomInt(int a, int b)
{
    std::uniform_int_distribution<> distr(a, b);
    return distr(gen);
}

float RandomGen::getRandomFloat(float a, float b)
{
    std::uniform_real_distribution<> distr(a, b);
    return distr(gen);
}

float RandomGen::getRandomFloat()
{
    std::uniform_real_distribution<> distr(0, 1);
    return distr(gen);
}