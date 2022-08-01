#include "game.h"
#include "config.h"
#include "randomGen.h"
#include "factory.h"
#include "tools.h"
#include <algorithm>

void Game::initialize()
{
    Tools::log("start game initialization");
    initFood();
    initCreatures();
    Tools::log("game initialization done");
}

std::vector<Frame> Game::run(bool recordRun)
{
    std::vector<Frame> frames;

    initialize();

    if (recordRun)
    {
        addFrame(frames);
    }

    int turn = 0;
    Tools::log("game started");
    while (turn < config::GAME_TURN && !m_creatures.empty())
    {
        updateCreatures();
        performCreaturesAction();
        
        if (recordRun)
        {
            addFrame(frames);
        }
    }
    Tools::log("game ended");
    return frames;
}

void Game::addFrame(std::vector<Frame>& frames)
{
    Frame frame;
    for (const auto& creature : m_creatures)
        frame.creatures.push_back(creature.toFrameCreature());
    for (const auto& food : m_food)
        frame.food.push_back(food.toFrameFood());
    frames.push_back(frame);
}

void Game::initFood()
{
    m_food.clear();
    int foodNumber = RandomGen::getRandomInt(config::FOOD_NUMBER_MIN, config::FOOD_NUMBER_MAX);
    for (int i = 0; i < foodNumber; i++)
    {
        m_food.emplace_back(Factory::createRandomFood());
    }
}

void Game::initCreatures()
{
    m_creatures.clear();
    for (int i = 0; i < config::CREATURE_POP_NUMBER; i++)
    {
        m_creatures.emplace_back(Factory::createRandomCreatures());
    }
}

void Game::performCreaturesAction()
{
    for (auto& creature : m_creatures)
    {
        creature.performAction();
    }
}

void Game::updateCreatures()
{
    for (auto& creature : m_creatures)
    {
        creature.decayHealth();
        if (creature.isAlive())
        {
            creature.pickRandomAction();
        }
    }
    m_creatures.erase(std::remove_if(m_creatures.begin(), m_creatures.end(), [](auto& creature){return !creature.isAlive();}));
}