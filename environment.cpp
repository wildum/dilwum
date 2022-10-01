#include "environment.h"
#include "tools.h"
#include "game.h"
#include "randomGen.h"
#include "creatureEntity.h"
#include "foodEntity.h"
#include "brainDrawer.h"
#include "serializer.h"

#include <SFML/Graphics.hpp>

#include <iostream>

sf::Image Environment::creatureImage;
sf::Texture Environment::creatureTexture;
sf::Font Environment::debugFont;

void Environment::initialize()
{
    tools::log("start initialization");
    RandomGen::initialize();
    loadAssets();
    tools::log("initialization done");
}

void Environment::runReplay(std::string& fileName)
{
    initialize();
    GameFeedback gamefeedback = Serializer::read(fileName);
    play(gamefeedback);
}

void Environment::runRaw()
{
    initialize();
    Game game;
    GameFeedback gamefeedback = game.run();
    tools::pause();
    play(gamefeedback);
    Serializer::write(gamefeedback);
}

void Environment::runRework(std::string& fileName)
{
    initialize();
    Game game;
    GameFeedback lastFeedback = Serializer::read(fileName);
    GameFeedback gamefeedback = game.run(lastFeedback.creatures);
    tools::pause();
    play(gamefeedback);
    Serializer::write(gamefeedback);
}

void Environment::play(GameFeedback& gamefeedback)
{
    int turnCount = 1;

    BrainDrawer brainDrawer;

    if (!gamefeedback.frames.empty())
    {
        sf::RenderWindow window(sf::VideoMode(2000, 1000), "Dilwum");

        auto creatureMap = initCreaturesEntities(window, gamefeedback.frames[0]);
        auto foodMap = initFoodEntities(window, gamefeedback.frames[0]);

        sf::Clock deltaClock;

        auto currentFrameIterator = gamefeedback.frames.begin();
        auto nextFrameIterator = currentFrameIterator + 1;
        float turnTime = 0;
        bool paused = false;
        tools::log("start displaying");
        while (window.isOpen() && nextFrameIterator != gamefeedback.frames.end())
        {
            if (!paused)
            {
                float dt = deltaClock.restart().asSeconds();
                turnTime += dt;
                if (turnTime > Config::getTURN_TIME_SECOND())
                {
                    currentFrameIterator++;
                    nextFrameIterator++;
                    turnTime -= Config::getTURN_TIME_SECOND();
                    turnCount++;
                    tools::log(std::to_string(turnCount));

                    if (nextFrameIterator == gamefeedback.frames.end())
                        break;
                }
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    onPressingMouseButton(brainDrawer, gamefeedback, currentFrameIterator, event.mouseButton.x, event.mouseButton.y);
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    paused = !paused;
                    tools::log(paused ? "paused" : "unpaused");
                }
            }
            if (!paused)
            {
                window.clear(Config::getBACKGROUND_COLOR());
                updateEntities(window, creatureMap, foodMap, currentFrameIterator, nextFrameIterator, turnTime / Config::getTURN_TIME_SECOND());
                window.display();
            }
        }
        tools::log("end of display");
    }
    else
    {
        tools::log("not recording ?");
    }
}

void Environment::onPressingMouseButton(BrainDrawer& brainDrawer, GameFeedback& gameFeedback, std::vector<Frame>::iterator& frameIterator, int x, int y)
{
    for (auto& frameCreature : frameIterator->creatures)
    {
        if (tools::squaredDist(x, y, frameCreature.position.x, frameCreature.position.y) < Config::getCREATURE_RADIUS() * Config::getCREATURE_RADIUS())
        {
            for (auto& creature : gameFeedback.creatures)
            {
                if (creature.getId() == frameCreature.id)
                {
                    brainDrawer.drawBrain(creature.getBrain());
                    break;
                }
            }
            break;
        }
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
            auto foodEntity = foods.find(foodNext.id);
            foodEntity->second.updateColor(foodNext);
            foodEntity->second.updateText(foodNext.value);
            foodEntity->second.draw(window);
        }
        else
        {
            auto it = foods.insert({foodNext.id, {foodNext, debugFont}});
            it.first->second.draw(window);
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
            creatureEntity->second.move(newPosition);
            creatureEntity->second.shape.setRotation(newDirection);
            creatureEntity->second.updateText(nextCreature.health);
            creatureEntity->second.draw(window);
        }
        else
        {
            auto it = creatures.insert({nextCreature.id, {nextCreature, creatureTexture, debugFont}});
            it.first->second.draw(window);
        }
    }
}

std::unordered_map<size_t, CreatureEntity> Environment::initCreaturesEntities(sf::RenderWindow& window, Frame& firstFrame)
{
    std::unordered_map<size_t, CreatureEntity> creatureMap;
    for (const auto& creature : firstFrame.creatures)
    {
        creatureMap.insert({creature.id, {creature, creatureTexture, debugFont}});
    }
    return creatureMap;
}

std::unordered_map<size_t, FoodEntity> Environment::initFoodEntities(sf::RenderWindow& window, Frame& firstFrame)
{
    std::unordered_map<size_t, FoodEntity> foodMap;
    for (const auto& food : firstFrame.food)
    {
        foodMap.insert({food.id, {food, debugFont}});
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
    if (!debugFont.loadFromFile("assets/arial.ttf"))
    {
        tools::log("cant load the font !");
        return;
    }
    tools::log("assets loaded");
}