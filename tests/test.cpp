#include "../creature.h"
#include "../food.h"
#include "../tools.h"
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
        tools::log("All tests ran fine");
    }

    void creatureMoveFoward()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Action::MOVE_FORWARD);
        std::vector<Food> food;
        creature.performAction(food);
        Vec expectedPosition{105.196f, 53.f};
        Vec diff = creature.getPosition() - expectedPosition;
        assert(diff.x + diff.y < 0.1);
    }

    void creatureTurnRight()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Action::ROTATE_RIGHT);
        std::vector<Food> food;
        creature.performAction(food);
        assert(creature.getAngle() == 0);
    }

    void creatureTurnLeft()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Action::ROTATE_LEFT);
        std::vector<Food> food;
        creature.performAction(food);
        assert(creature.getAngle() == 60);
    }

    void creatureEat()
    {
        // eating dist is 29
        Creature creature{Vec{100, 50}, 30, 0};
        creature.decayHealth();
        creature.decayHealth();
        creature.setAction(Action::EAT);
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
}