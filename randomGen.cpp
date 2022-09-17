#include "randomGen.h"
#include <time.h>

std::mt19937 RandomGen::gen;

void RandomGen::initialize()
{
    std::random_device r;
    gen = std::mt19937{(unsigned int) time(0)};
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

bool RandomGen::flipCoin()
{
    std::uniform_real_distribution<> distr(0, 1);
    return distr(gen) > 0.5;
}