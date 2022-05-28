#include "game.h"
#include "config.h"
#include "randomGen.h"
#include "factory.h"
#include <algorithm>

void Game::initialize()
{
    initFood();
    initCreatures();
}

void Game::run(std::vector<Frame>& frames, bool recordRun)
{
    initialize();

    if (recordRun)
    {
        addFrame(frames);
    }

    int turn = 0;
    while (turn < config::GAME_TURN && !m_creatures.empty())
    {
        updateCreatures();
        performCreaturesAction();
        
        if (recordRun)
        {
            addFrame(frames);
        }
    }
    
}

void Game::addFrame(std::vector<Frame>& frames)
{
    Frame frame;
    for (const auto& creature : m_creatures)
        frame.creatures.push_back(creature.toFrameCreature());
    for (const auto& food : m_food)
        frame.food.push_back(food.toFrameFood());
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
    m_creatures.erase(std::remove_if(m_creatures.begin(), m_creatures.end(), [](const auto& creature){return !creature.isAlive();}));
}