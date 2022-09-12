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

float fitness(const Creature& creature)
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
        auto& parent1 = creatures[RandomGen::getRandomInt(0, parentMaxIndex)];
        auto& parent2 = creatures[RandomGen::getRandomInt(0, parentMaxIndex)];
        std::vector<uint32_t> dna;
        for (int i = 0; i < std::max(parent1.getBrain().getGenome().size(), parent2.getBrain().getGenome().size()); i++)
        {
            Creature& parent = RandomGen::flipCoin() ? parent1 : parent2;
            if (parent.getBrain().getGenome().size() < i)
            {
                dna.push_back(parent.getBrain().getGenome()[i]);
            }
        }
        Creature creature = Factory::createCreature(dna);
        creature.getBrain().setInternalNeuronNumber(std::max(parent1.getBrain().getInternalNeuronsNumber(), parent2.getBrain().getInternalNeuronsNumber()));
        creatures.emplace_back(creature);
    }
}

void Ga::mutation(std::vector<Creature>& creatures, int turn)
{
    float mutationRate = tools::lerp(config::GA_MUTATION_RATE_MAX, config::GA_MUTATION_RATE_MIN, (float) turn / config::GAME_TURN);
    for (auto& creature : creatures)
    {
        for (int i = 0; i < creature.getBrain().getGenome().size(); i++)
        {
            if (RandomGen::getRandomFloat() < mutationRate)
            {
                int bitChanged = RandomGen::getRandomInt(0, 31);
                creature.getBrain().getGenome()[i] ^= 1UL << bitChanged;
                creature.getBrain().getGenome()[i] = gene::correctGene(creature.getBrain().getGenome()[i], neuron::INPUT_NUMBER, creature.getBrain().getInternalNeuronsNumber(), neuron::OUTPUT_NUMBER);
            }
        }
    }
}