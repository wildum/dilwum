#include "environment.h"
#include "tools.h"
#include "game.h"
#include "randomGen.h"

#include <SFML/Graphics.hpp>

sf::Image Environment::creatureImage;
sf::Texture Environment::creatureTexture;

void Environment::initialize()
{
    tools::log("start initialization");
    RandomGen::initialize();
    loadAssets();
    tools::log("initialization done");
}

void Environment::run()
{
    initialize();

    Game game;

    bool recordRun = true;
    std::vector<Frame> frames = game.run(recordRun);

    int turnCount = 1;

    if (recordRun && !frames.empty())
    {
        sf::RenderWindow window(sf::VideoMode(2000, 1000), "Dilwum");

        auto creatureMap = initCreaturesEntities(window, frames[0]);
        auto foodMap = initFoodEntities(window, frames[0]);

        sf::Clock deltaClock;

        auto currentFrameIterator = frames.begin();
        auto nextFrameIterator = currentFrameIterator + 1;
        float turnTime = 0;
        tools::log("start displaying");
        while (window.isOpen() && nextFrameIterator != frames.end())
        {
            float dt = deltaClock.restart().asSeconds();
            turnTime += dt;
            if (turnTime > config::TURN_TIME_SECOND)
            {
                currentFrameIterator++;
                nextFrameIterator++;
                turnTime -= config::TURN_TIME_SECOND;
                turnCount++;
                tools::log(std::to_string(turnCount));

                if (nextFrameIterator == frames.end())
                    break;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(config::BACKGROUND_COLOR);
            updateEntities(window, creatureMap, foodMap, currentFrameIterator, nextFrameIterator, turnTime / config::TURN_TIME_SECOND);
            window.display();
        }
        tools::log("end of display");
    }
    else
    {
        tools::log("not recording ?");
    }
}

void Environment::updateEntities(sf::RenderWindow& window,
    std::unordered_map<size_t, CreatureEntity>& creatures,
    std::unordered_map<size_t, FoodEntity>& foods,
    const std::vector<Frame>::iterator& currentFrameIterator,
    const std::vector<Frame>::iterator& nextFrameIterator,
    float time)
{
    for (const auto& foodNext : nextFrameIterator->food)
    {
        auto foodCurrent = std::find_if(currentFrameIterator->food.begin(), currentFrameIterator->food.end(), [&foodNext](const auto& foodCurrent){return foodCurrent.id == foodNext.id;});

        if (foodCurrent != currentFrameIterator->food.end())
        {
            auto creatureEntity = foods.find(foodNext.id);
            creatureEntity->second.updateColor(foodNext);
            window.draw(creatureEntity->second.shape);
        }
        else
        {
            auto it = foods.insert({foodNext.id, {foodNext}});
            window.draw(it.first->second.shape);
        }
    }
    for (const auto& nextCreature : nextFrameIterator->creatures)
    {
        auto currentCreature = std::find_if(currentFrameIterator->creatures.begin(), currentFrameIterator->creatures.end(), [&nextCreature](const auto& creatureCurrent){return creatureCurrent.id == nextCreature.id;});

        if (currentCreature != currentFrameIterator->creatures.end())
        {
            auto creatureEntity = creatures.find(nextCreature.id);
            Vec newPosition = Vec::lerp(currentCreature->position, nextCreature.position, time);
            float newDirection = tools::lerp(currentCreature->angle, nextCreature.angle, time);
            creatureEntity->second.shape.setPosition(newPosition.x, newPosition.y);
            creatureEntity->second.shape.setRotation(newDirection);
            window.draw(creatureEntity->second.shape);
        }
        else
        {
            auto it = creatures.insert({nextCreature.id, {nextCreature, creatureTexture}});
            window.draw(it.first->second.shape);
        }
    }
}

std::unordered_map<size_t, CreatureEntity> Environment::initCreaturesEntities(sf::RenderWindow& window, Frame& firstFrame)
{
    std::unordered_map<size_t, CreatureEntity> creatureMap;
    for (const auto& creature : firstFrame.creatures)
    {
        creatureMap.insert({creature.id, {creature, creatureTexture}});
    }
    return creatureMap;
}

std::unordered_map<size_t, FoodEntity> Environment::initFoodEntities(sf::RenderWindow& window, Frame& firstFrame)
{
    std::unordered_map<size_t, FoodEntity> foodMap;
    for (const auto& food : firstFrame.food)
    {
        foodMap.insert({food.id, {food}});
    }
    return foodMap;
}

void Environment::loadAssets()
{
    if (!Environment::creatureTexture.loadFromFile("assets/creature.png"))
    {
        tools::log("cant load the image !");
        return;
    }
    tools::log("assets loaded");
}