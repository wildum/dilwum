#include "../creature.h"
#include "../food.h"
#include "../tools.h"
#include "../gene.h"
#include "../brain.h"
#include "../brainDrawer.h"
#include "../ga.h"
#include "../factory.h"
#include "../randomGen.h"
#include "test.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

namespace test
{
    void runAllTests()
    {
        RandomGen::initialize();
        creatureMoveFoward();
        creatureTurnRight();
        creatureTurnLeft();
        creatureEat();
        checkCorrectGene();
        checkCorrectGene2();
        //checkBrainConnectionsOrdering();
        checkBrainProcess();
        checkGASelection();
        checkGA();
        checkGenomeCorrection();
        checkInternalNodesCounting();
        checkTasteSetCorrectly();
        tools::log("All tests passed");
    }

    void creatureMoveFoward()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setSpeed(6);
        creature.setAction(Output::MOVE_FORWARD);
        std::vector<Food> food;
        creature.performAction(food);
        Vec expectedPosition{105.196f, 53.f};
        Vec diff = creature.getPosition() - expectedPosition;
        assert(diff.x + diff.y < 0.1);
    }

    void creatureTurnRight()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Output::ROTATE_RIGHT);
        std::vector<Food> food;
        creature.performAction(food);
        assert(creature.getAngle() == 0);
    }

    void creatureTurnLeft()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Output::ROTATE_LEFT);
        std::vector<Food> food;
        creature.performAction(food);
        assert(creature.getAngle() == 60);
    }

    void creatureEat()
    {
        // eating dist is 29
        Creature creature{Vec{100, 50}, 30, 0};
        creature.decayHealth(0);
        creature.decayHealth(0);
        creature.setAction(Output::EAT);
        std::vector<Food> food;
        Food f1{{130, 60}, 10, 0};
        food.push_back(f1);
        creature.performAction(food); // no eating
        assert(creature.getHealth() == 98);
        assert(food[0].getValue() == 10);
        Food f2{{120, 60}, 10, 0};
        food.push_back(f2);
        creature.performAction(food); // eating
        assert(creature.getHealth() == 100);
        assert(food[0].getValue() == 10);
        assert(food[1].getValue() == 9);
    }

    void checkCorrectGene()
    {
        // 1 1011001 0 1011110 0100101101010101
        uint32_t gene = 0b11011001010111100100101101010101;

        uint32_t correctedGene = gene::correctGene(gene, 5, 8, 3);
        int senderType = correctedGene >> 31;
        int receiverType = (correctedGene >> 23) & 1;
        int senderId = (correctedGene >> 24) & 127;
        int receiverId = (correctedGene >> 16) & 127;
        int weight = correctedGene & 65535;
        assert(senderType == 1);
        assert(senderId == 3);
        assert(receiverType == 0);
        assert(receiverId == 5);
        assert(weight == 19285);
    }

    void checkCorrectGene2()
    {
        // 0 0000011 1 0111111 1110101110101010
        uint32_t gene = 0b00000011101111111110101110101010;

        uint32_t correctedGene = gene::correctGene(gene, 2, 4, 6);
        int senderType = correctedGene >> 31;
        int receiverType = (correctedGene >> 23) & 1;
        int senderId = (correctedGene >> 24) & 127;
        int receiverId = (correctedGene >> 16) & 127;
        int weight = correctedGene & 65535;
        assert(senderType == 0);
        assert(senderId == 0);
        assert(receiverType == 1);
        assert(receiverId == 2);
        assert(weight == 60330);
    }

    void checkBrainConnectionsOrdering()
    {
        Brain brain;
        BrainDrawer brainDrawer;
        tools::log(brain.getConnection().size());
        for (const auto& connection : brain.getConnection())
        {
            std::cout << "Connection: " << connection.id << std::endl;
        }
        brainDrawer.drawBrain(brain);
    }

    void checkBrainProcess()
    {
        std::vector<uint32_t> genome;
        BrainDrawer brainDrawer;
        genome.push_back(gene::generateSpecificConnectionGene(1, 0, 0, 0, 2));
        genome.push_back(gene::generateSpecificConnectionGene(1, 0, 0, 1, -2));
        genome.push_back(gene::generateSpecificConnectionGene(1, 1, 0, 1, 3));
        genome.push_back(gene::generateSpecificConnectionGene(0, 0, 1, 0, 1));
        genome.push_back(gene::generateSpecificConnectionGene(0, 1, 0, 0, 1));
        genome.push_back(gene::generateSpecificConnectionGene(0, 1, 1, 0, -3));
        genome.push_back(gene::generateSpecificConnectionGene(0, 1, 1, 1, 2));
        Brain brain(genome);
        brain.setHealth(50); // 0.5
        brain.setTaste(Taste::TASTE_FOOD); // 1.0
        // -1 D
        // 1 C
        // 3 D
        // D value = 0.9640
        // 0.9640 C
        // 1.928 E
        // -2.892 F
        // C value = 0.9610
        // 0.9610 F
        // E output = 0.95
        // F output = -0.95
        brain.process();
        Output action = brain.pickAction();
        assert(action == ROTATE_RIGHT);
    }

    void checkGASelection()
    {
        Ga ga;
        std::vector<Creature> creatures;
        for (int i = 0; i < Config::getPOP_NUMBER(); i++)
        {
            Creature c = Creature({0, 0}, 0, i);
            c.setHealth(i);
            creatures.push_back(c);
        }
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(creatures), std::end(creatures), rng);
        ga.selection(creatures);
        assert(creatures.size() == Config::getPOP_NUMBER() / 2);
        assert(creatures[0].getHealth() == Config::getPOP_NUMBER() - 1);
        assert(creatures[1].getHealth() == Config::getPOP_NUMBER() - 2);
    }

    void checkGA()
    {
        Ga ga;
        std::vector<Creature> creatures;
        for (int i = 0; i < Config::getPOP_NUMBER(); i++)
        {
            Creature c = Creature({0, 0}, 0, i);
            c.setHealth(i);
            creatures.push_back(c);
        }
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(creatures), std::end(creatures), rng);
        ga.computeNextGen(creatures, 0);
        assert(creatures.size() == Config::getPOP_NUMBER());
        ga.computeNextGen(creatures, 1000);
        assert(creatures.size() == Config::getPOP_NUMBER());
    }

    void checkGenomeCorrection()
    {
        std::vector<uint32_t> genome;
        uint32_t gene1 = gene::generateSpecificConnectionGene(1, 1, 1, 1, 3);
        uint32_t gene2 = gene::generateSpecificConnectionGene(0, 1, 0, 1, 4);
        uint32_t gene3 = gene::generateSpecificConnectionGene(1, 1, 0, 1, 4);
        uint32_t gene4 = gene::generateSpecificConnectionGene(1, 1, 1, 1, -4);
        uint32_t gene5 = gene::generateSpecificConnectionGene(1, 1, 0, 1, -1);
        uint32_t gene6 = gene::generateSpecificConnectionGene(1, 9, 0, 4, -3);
        uint32_t gene7 = gene::generateSpecificConnectionGene(1, 9, 0, 4, 3);
        genome.push_back(gene1);
        genome.push_back(gene2);
        genome.push_back(gene3);
        genome.push_back(gene4);
        genome.push_back(gene5);
        genome.push_back(gene6);
        genome.push_back(gene7);
        auto correctedGenome = gene::correctGenome(genome);
        assert(correctedGenome.size() == 4);
        assert(correctedGenome[0] == gene1);
        assert(correctedGenome[1] == gene2);
        assert(correctedGenome[2] == gene3);
        assert(correctedGenome[3] == gene6);
    }

    void checkInternalNodesCounting()
    {
        std::vector<uint32_t> genome;
        uint32_t gene1 = gene::generateSpecificConnectionGene(1, 1, 1, 1, 3);
        uint32_t gene2 = gene::generateSpecificConnectionGene(0, 1, 0, 1, 4);
        uint32_t gene3 = gene::generateSpecificConnectionGene(1, 1, 0, 1, 4);
        uint32_t gene4 = gene::generateSpecificConnectionGene(1, 1, 1, 1, -4);
        uint32_t gene5 = gene::generateSpecificConnectionGene(1, 1, 0, 1, -1);
        uint32_t gene6 = gene::generateSpecificConnectionGene(1, 9, 0, 4, -3);
        uint32_t gene7 = gene::generateSpecificConnectionGene(1, 9, 0, 4, 3);
        genome.push_back(gene1);
        genome.push_back(gene2);
        genome.push_back(gene3);
        genome.push_back(gene4);
        genome.push_back(gene5);
        genome.push_back(gene6);
        genome.push_back(gene7);
        Ga ga;
        int numberOfInternalNodes = ga.getNumberOfInternalNodes(genome);
        assert(numberOfInternalNodes == 2);
    }

    void checkTasteSetCorrectly()
    {
        std::vector<Creature> creatures;
        Creature creature{Vec{100, 50}, 30, 0};
        std::vector<Food> food;
        Food f2{{120, 60}, 10, 0};
        food.push_back(f2);
        creature.processInputs(food, creatures);
        assert(creature.getBrain().getTaste() == 1.0);
        food.clear();
        creature.processInputs(food, creatures);
        assert(creature.getBrain().getTaste() == 0.0);
        Food f1{{130, 60}, 10, 0};
        food.push_back(f1);
        creature.processInputs(food, creatures);
        assert(creature.getBrain().getTaste() == 0.0); // out of range
        food.push_back(f2);
        creature.processInputs(food, creatures);
        assert(creature.getBrain().getTaste() == 1.0);
    }
}