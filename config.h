#ifndef CONFIG
#define CONFIG

#include <SFML/Graphics.hpp>

namespace config
{
    const float TURN_TIME_SECOND = 0.5;

    const int GENOME_SIZE_MAX = 50; // max 8 bits
    const int INTERNAL_NEURON_NUMBER_MAX = 15; // max 8 bits

    const int GENERATIONS = 1000;
    const float GA_POP_RETAINED_RATIO = 0.5;
    const float GA_MUTATION_RATE_MIN = 0.01;
    const float GA_MUTATION_RATE_MAX = 0.2;

    const int MAP_WIDTH = 2500;
    const int MAP_HEIGHT = 1000;

    const int GAME_TURN = 1000;

    const int CREATURE_RADIUS = 9;
    const int CREATURE_POP_NUMBER = 100;
    const int CREATURE_HEALTH = 100;
    const int CREATURE_SPEED = 6;
    const int CREATURE_ROTATION_DEGREE = 30;
    const int CREATURE_EATING_VALUE = 10;
    const int CREATURE_ECHOLOCATION_DISTANCE = 50;
    const int CREATURE_ANTENNA_Y_OFFSET = 3;
    const int CREATURE_ANTENNA_X_OFFSET = 4;

    const int FOOD_NUMBER_MIN = 70;
    const int FOOD_NUMBER_MAX = 100;
    const int FOOD_VALUE_MIN = 5;
    const int FOOD_VALUE_MAX = 20;
    const int FOOD_RADIUS = 20;

    const float EPSILON = 0.000001;

    const sf::Color BACKGROUND_COLOR{220, 220, 220};
    const sf::Color FOOD_COLOR{34, 139, 34};
}
#endif