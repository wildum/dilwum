#include "../creature.h"
#include "../food.h"
#include "../tools.h"
#include "../gene.h"
#include "../brain.h"
#include "../brainDrawer.h"
#include "test.h"
#include <cassert>
#include <vector>

namespace test
{
    void runAllTests()
    {
        creatureMoveFoward();
        creatureTurnRight();
        creatureTurnLeft();
        creatureEat();
        checkCorrectGene();
        checkCorrectGene2();
        //checkBrainConnectionsOrdering();
        checkBrainProcess();
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
}