#ifndef GA
#define GA

#include "creature.h"

class Ga
{
public:
    void computeNextGen(std::vector<Creature>& creatures, int turn);
private:
    void selection(std::vector<Creature>& creatures);
    void crossover(std::vector<Creature>& creatures);
    void mutation(std::vector<Creature>& creatures, int turn);
    inline float fitness(const Creature& creature);
};

#endif