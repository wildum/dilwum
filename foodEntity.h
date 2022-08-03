#ifndef FOOD_ENTITY
#define FOOD_ENTITY

#include <SFML/Graphics.hpp>

#include "creature.h"
#include "food.h"

class FoodEntity
{
    public:
        size_t id;
        sf::CircleShape shape;
        sf::Text valueText;

        FoodEntity(const FrameFood& frameFood, const sf::Font& font);
        void updateColor(const FrameFood& frameFood);
        void updateText(int value);
        void draw(sf::RenderWindow& window);
};

#endif