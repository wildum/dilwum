#ifndef GAME
#define GAME

#include <vector>
#include "food.h"
#include "creature.h"
#include "frame.h"
#include "ga.h"

struct GameFeedback
{
    std::vector<Frame> frames;
    std::vector<Creature> creatures;
};

class Game
{
public:
    GameFeedback run();
private:
    void addFrame(std::vector<Frame>& frames);
    void initialize();
    void initFood();
    void initCreatures();
    bool updateCreatures(int turn);
    void updateFood();
    void performCreaturesAction();
    void logGameInfo(int currentGeneration);
    std::vector<Food> m_food;
    std::vector<Creature> m_creatures;
    Ga ga;
};

#endif