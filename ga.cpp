#include "ga.h"
#include "randomGen.h"
#include "factory.h"
#include "gene.h"
#include <algorithm>
#include <vector>

void Ga::computeNextGen(std::vector<Creature>& creatures, int turn)
{
    selection(creatures);
    crossover(creatures);
    mutation(creatures, turn);
}

float Ga::fitness(const Creature& creature)
{
    return creature.isAlive() ? creature.getHealth() : creature.getDeadAt() / (float) config::GAME_TURN;
}

void Ga::selection(std::vector<Creature>& creatures)
{
    int creaturesToKeep = config::CREATURE_POP_NUMBER * config::GA_POP_RETAINED_RATIO;
    for (auto& creature : creatures)
    {
        float score = fitness(creature);
        creature.setScore(score);
    }
    std::partial_sort(creatures.begin(), creatures.begin() + creaturesToKeep, creatures.end(), [this](const Creature& c1, const Creature& c2){
        return c1.getScore() > c2.getScore();
    });
    creatures.erase(creatures.begin() + creaturesToKeep, creatures.end());
}

void Ga::crossover(std::vector<Creature>& creatures)
{
    int parentMaxIndex = creatures.size() - 1;
    while (creatures.size() < config::CREATURE_POP_NUMBER)
    {
        // ignore collisions
        int parent1Index = RandomGen::getRandomInt(0, parentMaxIndex);
        int parent2Index = RandomGen::getRandomInt(0, parentMaxIndex);
        std::vector<uint32_t> dna;
        for (int i = 0; i < std::max(creatures[parent1Index].getBrain().getGenome().size(), creatures[parent2Index].getBrain().getGenome().size()); i++)
        {
            int parentIndex = RandomGen::flipCoin() ? parent1Index : parent2Index;
            if (i < creatures[parentIndex].getBrain().getGenome().size())
            {
                dna.push_back(creatures[parentIndex].getBrain().getGenome()[i]);
            }
        }
        Creature creature = Factory::createCreature(std::move(dna));
        creature.getBrain().setInternalNeuronNumber(std::max(creatures[parent1Index].getBrain().getInternalNeuronsNumber(), creatures[parent2Index].getBrain().getInternalNeuronsNumber()));
        creatures.emplace_back(creature);
    }
}

void Ga::mutation(std::vector<Creature>& creatures, int turn)
{
    float mutationRate = tools::lerp(config::GA_MUTATION_RATE_MAX, config::GA_MUTATION_RATE_MIN, (float) turn / config::GAME_TURN);
    // uncomment if testing needed
    // double test = 0;
    // int testMutatedCrea = 0;
    for (auto& creature : creatures)
    {
        // bool changed = false;
        // int tempTest = 0;
        for (int i = 0; i < creature.getBrain().getGenome().size(); i++)
        {
            if (RandomGen::getRandomFloat() < mutationRate)
            {
                // tempTest++;
                // changed = true;
                int bitChanged = RandomGen::getRandomInt(0, 31);
                creature.getBrain().getGenome()[i] ^= 1UL << bitChanged;
                creature.getBrain().getGenome()[i] = gene::correctGene(creature.getBrain().getGenome()[i], neuron::INPUT_NUMBER, creature.getBrain().getInternalNeuronsNumber(), neuron::OUTPUT_NUMBER);
            }
        }
        // if (tempTest != 0)
        //     test += (double) tempTest / creature.getBrain().getGenome().size();
        // testMutatedCrea += changed;
    }
    // std::cout << "Gene changed : " << ((double) test / creatures.size()) * 100 << " %" << std::endl;
    // std::cout << "Creatures changed : " << ((double) testMutatedCrea / creatures.size()) * 100 << " %" << std::endl;
}