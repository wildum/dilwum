#include "game.h"
#include "config/config.h"
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

    while (currentGeneration < Config::getGENERATIONS())
    {
        bool lastRun = currentGeneration == Config::getGENERATIONS() - 1;
        if (lastRun)
        {
            addFrame(gameFeedback.frames);
        }

        int turn = 0;
        bool alive = true;
        initFood();
        while (turn < Config::getGAME_TURN() && alive)
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
    int genomeSize = 0;
    for (auto& creature : m_creatures)
    {
        genomeSize += creature.getBrain().getGenome().size();
        if (creature.isAlive())
        {
            survivors += 1;
            averageTurnSurvived += Config::getGAME_TURN();
        }
        else
        {
            averageTurnSurvived += creature.getDeadAt();
        }
    }
    tools::log("Generation: " + std::to_string(currentGeneration) + ": " + std::to_string(survivors)
        + " survived, averageTurnSurvived: " + std::to_string((float) averageTurnSurvived / m_creatures.size())
        + ", genome average size: " + std::to_string((float) genomeSize / m_creatures.size()));
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
    int foodNumber = RandomGen::getRandomInt(Config::getFOOD_NUMBER_MIN(), Config::getFOOD_NUMBER_MAX());
    for (int i = 0; i < foodNumber; i++)
    {
        m_food.emplace_back(Factory::createRandomFood());
    }
}

void Game::initCreatures()
{
    m_creatures.clear();
    for (int i = 0; i < Config::getPOP_NUMBER(); i++)
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