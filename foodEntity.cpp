#include "foodEntity.h"
#include "environment.h"

FoodEntity::FoodEntity(const FrameFood& frameFood, const sf::Font& font)
{
    id = frameFood.id;
    shape.setRadius(config::FOOD_RADIUS);
    updateColor(frameFood);
    shape.setOrigin(config::FOOD_RADIUS, config::FOOD_RADIUS);
    shape.setPosition(frameFood.position.x, frameFood.position.y);
    valueText.setPosition(frameFood.position.x, frameFood.position.y);
    valueText.setFillColor(sf::Color::Blue);
    valueText.setFont(font);
    valueText.setCharacterSize(15);
    updateText(frameFood.value);
}

void FoodEntity::updateColor(const FrameFood& frameFood)
{
    sf::Color color = config::FOOD_COLOR;
    color.a = std::max(frameFood.value * 255 / config::FOOD_VALUE_MAX, 10);
    shape.setFillColor(color);
}

void FoodEntity::updateText(int value)
{
    valueText.setString(std::to_string(value));
}

void FoodEntity::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    if (Environment::debugMode)
        window.draw(valueText);
}

    