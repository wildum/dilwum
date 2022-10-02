#include "ga.h"
#include "randomGen.h"
#include "factory.h"
#include "gene.h"
#include <algorithm>
#include <vector>
#include <unordered_set>

void Ga::computeNextGen(std::vector<Creature>& creatures, int turn)
{
    selection(creatures);
    crossover(creatures);
    mutation(creatures, turn);
    resetPopulation(creatures);
}

void Ga::resetPopulation(std::vector<Creature>& creatures)
{
    for (auto& creature : creatures)
    {
        std::vector<uint32_t> correctedGenome = gene::correctGenome(creature.getBrain().getGenome());
        creature.getBrain().setGenome(std::move(correctedGenome));
        creature.getBrain().buildBrain();
        creature.reset();
    }
}

float Ga::fitness(const Creature& creature)
{
    return creature.isAlive() ? creature.getHealth() : creature.getDeadAt() / (float) Config::getGAME_TURN();
}

void Ga::selection(std::vector<Creature>& creatures)
{
    int creaturesToKeep = Config::getPOP_NUMBER() * Config::getGA_POP_RETAINED_RATIO();
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
    while (creatures.size() < Config::getPOP_NUMBER())
    {
        // ignore collisions
        int parent1Index = RandomGen::getRandomInt(0, parentMaxIndex);
        int parent2Index = RandomGen::getRandomInt(0, parentMaxIndex);
        std::vector<uint32_t> dna;
        std::unordered_set<uint32_t> connectionSet;
        for (const auto& gene : creatures[parent1Index].getBrain().getGenome())
        {
            connectionSet.insert(((gene >> 31) << 31) | (((gene >> 24) & 127) << 24) | (((gene >> 23) & 1) << 23) | (((gene >> 16) & 127) << 16));
        }
        // if common then add, else 1/2 to add
        for (const auto& gene : creatures[parent2Index].getBrain().getGenome())
        {
            uint32_t connection = ((gene >> 31) << 31) | (((gene >> 24) & 127) << 24) | (((gene >> 23) & 1) << 23) | (((gene >> 16) & 127) << 16);
            auto it = connectionSet.find(connection);
            if (it != connectionSet.end())
            {
                dna.push_back(gene);
                connectionSet.erase(connection);
            }
            else if (RandomGen::flipCoin())
            {
                dna.push_back(gene);
            }
        }
        // 1/2 to add
        for (const auto& gene : creatures[parent1Index].getBrain().getGenome())
        {
            uint32_t connection = ((gene >> 31) << 31) | (((gene >> 24) & 127) << 24) | (((gene >> 23) & 1) << 23) | (((gene >> 16) & 127) << 16);
            if (connectionSet.find(connection) != connectionSet.end() && RandomGen::flipCoin())
            {
                dna.push_back(gene);
            }
        }
        Creature creature = Factory::createCreature(std::move(dna));
        creatures.emplace_back(creature);
    }
}

void Ga::mutation(std::vector<Creature>& creatures, int turn)
{
    float mutationRate = tools::lerp(Config::getGA_MUTATION_RATE_MAX(), Config::getGA_MUTATION_RATE_MIN(), (float) turn / Config::getGAME_TURN());
    // uncomment if testing needed
    // double test = 0;
    // int testMutatedCrea = 0;
    for (auto& creature : creatures)
    {
        // bool changed = false;
        // int tempTest = 0;
        int numberOfInternalNodesPossible = getNumberOfInternalNodes(creature.getBrain().getGenome())+1;
        for (int i = 0; i < creature.getBrain().getGenome().size(); i++)
        {
            if (RandomGen::getRandomFloat() < mutationRate)
            {
                // tempTest++;
                // changed = true;
                int bitChanged = RandomGen::getRandomInt(0, 31);
                creature.getBrain().getGenome()[i] ^= 1UL << bitChanged;
                creature.getBrain().getGenome()[i] = gene::correctGene(creature.getBrain().getGenome()[i], neuron::INPUT_NUMBER, numberOfInternalNodesPossible, neuron::OUTPUT_NUMBER);
            }
        }
        // if (tempTest != 0)
        //     test += (double) tempTest / creature.getBrain().getGenome().size();
        // testMutatedCrea += changed;
    }
    // std::cout << "Gene changed : " << ((double) test / creatures.size()) * 100 << " %" << std::endl;
    // std::cout << "Creatures changed : " << ((double) testMutatedCrea / creatures.size()) * 100 << " %" << std::endl;
}

int Ga::getNumberOfInternalNodes(std::vector<unsigned int>& genome)
{
    std::unordered_set<int> nodes;
    for (auto gene : genome)
    {
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;

        if (senderType == gene::SenderType::SENDER_INTERNAL)
            nodes.insert(senderId);

        if (receiverType == gene::ReceiverType::RECEIVER_INTERNAL)
            nodes.insert(receiverId);
    }
    return nodes.size();
}