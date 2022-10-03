#include "creatureEntity.h"
#include "environment.h"

CreatureEntity::CreatureEntity(const FrameCreature& frameCreature, const sf::Texture& texture, const sf::Font& font)
{
    id = frameCreature.id;
    shape.setTexture(texture); // could make it smooth
    shape.setOrigin(sf::Vector2f(10.f, 16.f));
    debugShape.setRadius(Config::getCREATURE_RADIUS());
    debugShape.setFillColor(sf::Color::Red);
    debugShape.setOrigin(Config::getCREATURE_RADIUS(), Config::getCREATURE_RADIUS());
    debugShapeAntennaLeft.setRadius(3);
    debugShapeAntennaLeft.setFillColor(sf::Color::Red);
    debugShapeAntennaLeft.setOrigin(3, 3);
    debugShapeAntennaRight.setRadius(3);
    debugShapeAntennaRight.setFillColor(sf::Color::Red);
    debugShapeAntennaRight.setOrigin(3, 3);
    healthText.setFillColor(sf::Color::Blue);
    healthText.setFont(font);
    healthText.setCharacterSize(10);
    updateText(frameCreature.health);
    move(frameCreature.position, frameCreature.antennaLeftPosition, frameCreature.antennaRightPosition);
    shape.setRotation(frameCreature.angle);
}

void CreatureEntity::move(const Vec& position, const Vec& leftAntennaPosition, const Vec& rightAntennaPosition)
{
    healthText.setPosition(position.x, position.y);
    shape.setPosition(position.x, position.y);
    debugShape.setPosition(position.x, position.y);
    debugShapeAntennaLeft.setPosition(leftAntennaPosition.x, leftAntennaPosition.y);
    debugShapeAntennaRight.setPosition(rightAntennaPosition.x, rightAntennaPosition.y);
}

void CreatureEntity::updateText(int health)
{
    healthText.setString(std::to_string(health));
}

void CreatureEntity::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    if (Environment::debugMode)
    {
        window.draw(debugShape);
        window.draw(healthText);
        window.draw(debugShapeAntennaLeft);
        window.draw(debugShapeAntennaRight);
    }
}