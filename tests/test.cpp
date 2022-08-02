#include "../creature.h"
#include "../tools.h"
#include "test.h"
#include <cassert>

namespace test
{
    void runAllTests()
    {
        creatureMoveFoward();
        creatureTurnRight();
    }

    void creatureMoveFoward()
    {
        Creature creature{Vec{100, 50}, 30, 0};
        creature.setAction(Action::MOVE_FORWARD);
        creature.performAction();
        Vec expectedPosition{102.5980762113533f, 51.5};
        assert(creature.getPosition() == expectedPosition);
    }

    void creatureTurnRight()
    {
    }
}