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
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(frameFood.position.x, frameFood.position.y);
    }
};

#endif