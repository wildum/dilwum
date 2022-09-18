#include "game.h"
#include "config.h"
#include "randomGen.h"
#include "factory.h"
#include "tools.h"
#include <algorithm>

void Game::initialize()
{
    tools::log("start game initialization");
    initCreatures();
    tools::log("game initialization done");
}

GameFeedback Game::run()
{
    GameFeedback gameFeedback;

    initialize();

    int currentGeneration = 0;

    while (currentGeneration < config::GENERATIONS)
    {
        bool lastRun = currentGeneration == config::GENERATIONS - 1;
        if (lastRun)
        {
            addFrame(gameFeedback.frames);
        }

        int turn = 0;
        bool alive = true;
        initFood();
        while (turn < config::GAME_TURN && alive)
        {
            alive = updateCreatures(turn);
            updateFood();
            performCreaturesAction();
            
            if (lastRun)
            {
                addFrame(gameFeedback.frames);
            }
            turn++;
        }
        logGameInfo(currentGeneration);
        if (!lastRun)
        {
            // changes are applied directly on the pop
            ga.computeNextGen(m_creatures, turn);
        }
        currentGeneration++;
    }

    gameFeedback.creatures = m_creatures;

    return gameFeedback;
}

void Game::logGameInfo(int currentGeneration)
{
    int survivors = 0;
    int averageTurnSurvived = 0;
    for (const auto& creature : m_creatures)
    {
        if (creature.isAlive())
        {
            survivors += 1;
            averageTurnSurvived += config::GAME_TURN;
        }
        else
        {
            averageTurnSurvived += creature.getDeadAt();
        }
    }
    tools::log("Generation: " + std::to_string(currentGeneration) + ": " + std::to_string(survivors) + " survived, averageTurnSurvived: " + std::to_string((float) averageTurnSurvived / m_creatures.size()));
}

void Game::addFrame(std::vector<Frame>& frames)
{
    Frame frame;
    for (const auto& creature : m_creatures)
    {
        if (creature.isAlive())
            frame.creatures.push_back(creature.toFrameCreature());
    }
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
        m_creatures.emplace_back(Factory::createRandomCreature());
    }
}

void Game::performCreaturesAction()
{
    for (auto& creature : m_creatures)
    {
        if (creature.isAlive())
            creature.performAction(m_food);
    }
}

void Game::updateFood()
{
    m_food.erase(std::remove_if(m_food.begin(), m_food.end(), [&](auto& food){return food.isDepleted();}), m_food.end());
}

bool Game::updateCreatures(int turn)
{
    bool alive = false;
    for (auto& creature : m_creatures)
    {
        creature.decayHealth(turn);
        if (creature.isAlive())
        {
            alive = true;
            creature.processInputs(m_food, m_creatures);
            creature.pickAction();
        }
    }
    return alive;
}