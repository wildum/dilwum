#include "randomGen.h"

std::random_device RandomGen::rd;
std::mt19937 RandomGen::gen;

void RandomGen::initialize()
{
    gen = std::mt19937{rd()};
}

int RandomGen::getRandomInt(int a, int b)
{
    static std::uniform_int_distribution<> distr(a, b);
    return distr(gen);
}

float RandomGen::getRandomFloat(float a, float b)
{
    static std::uniform_real_distribution<> distr(a, b);
    return distr(gen);
}

float RandomGen::getRandomFloat()
{
    static std::uniform_real_distribution<> distr(0, 1);
    return distr(gen);
}

bool RandomGen::flipCoin()
{
    static std::uniform_real_distribution<> distr(0, 1);
    return distr(gen) > 0.5;
}