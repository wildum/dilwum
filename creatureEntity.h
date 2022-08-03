#ifndef CREATURE_ENTITY
#define CREATURE_ENTITY

#include <SFML/Graphics.hpp>

#include "creature.h"
#include "food.h"

class CreatureEntity
{
    public:
        size_t id;
        sf::Sprite shape;
        sf::CircleShape debugShape;
        sf::Text healthText;

        CreatureEntity(const FrameCreature& frameCreature, const sf::Texture& texture, const sf::Font& font);
        void move(const Vec& position);
        void updateText(int health);
        void draw(sf::RenderWindow& window);
};

#endif