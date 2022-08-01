#ifndef GAME
#define GAME

#include <vector>
#include "food.h"
#include "creature.h"
#include "frame.h"

class Game
{
public:
    std::vector<Frame> run(bool recordRun);
private:
    void addFrame(std::vector<Frame>& frames);
    void initialize();
    void initFood();
    void initCreatures();
    void updateCreatures();
    void performCreaturesAction();
    std::vector<Food> m_food;
    std::vector<Creature> m_creatures;
};

#endif