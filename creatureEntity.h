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
        sf::CircleShape debugShapeAntennaLeft;
        sf::CircleShape debugShapeAntennaRight;
        sf::Text healthText;

        CreatureEntity(const FrameCreature& frameCreature, const sf::Texture& texture, const sf::Font& font);
        void move(const Vec& position, const Vec& leftAntennaPosition, const Vec& rightAntennaPosition);
        void updateText(int health);
        void draw(sf::RenderWindow& window);
};

#endif