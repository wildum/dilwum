#ifndef ENTITIES_GRAPHIC
#define ENTITIES_GRAPHIC

#include <SFML/Graphics.hpp>

#include "environment.h"
#include "creature.h"
#include "food.h"

struct CreatureEntity
{
    size_t id;
    sf::Sprite shape;
    CreatureEntity(const FrameCreature& frameCreature, const sf::Texture& texture)
    {
        id = frameCreature.id;
        shape.setTexture(texture); // could make it smooth
        shape.setOrigin(sf::Vector2f(10.f, 16.f));
        shape.setPosition(frameCreature.position.x, frameCreature.position.y);
        shape.setRotation(frameCreature.angle);
    }
};

struct FoodEntity
{
    size_t id;
    sf::CircleShape shape;
    FoodEntity(const FrameFood& frameFood)
    {
        id = frameFood.id;
        shape.setRadius(config::FOOD_RADIUS);
        updateColor(frameFood);
        shape.setPosition(frameFood.position.x, frameFood.position.y);
    }

    void updateColor(const FrameFood& frameFood)
    {
        sf::Color color = config::FOOD_COLOR;
        color.a = std::max(frameFood.value * 255 / config::FOOD_VALUE_MAX, 50);
        shape.setFillColor(color);
    }
};

#endif