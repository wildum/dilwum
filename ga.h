#ifndef GA
#define GA

#include "creature.h"

class Ga
{
public:
    void computeNextGen(std::vector<Creature>& creatures, int turn);
    void selection(std::vector<Creature>& creatures);
    void crossover(std::vector<Creature>& creatures);
    void mutation(std::vector<Creature>& creatures, int turn);
    void resetPopulation(std::vector<Creature>& creatures);
    inline float fitness(const Creature& creature);
    int getNumberOfInternalNodes(std::vector<unsigned int>& genome);
};

#endif