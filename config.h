#ifndef CONFIG
#define CONFIG

namespace config
{
    const float TURN_TIME_SECOND = 1;

    const int MAP_WIDTH = 2500;
    const int MAP_HEIGHT = 1000;

    const int GAME_TURN = 1000;

    const int CREATURE_RADIUS = 9;
    const int CREATURE_POP_NUMBER = 100;
    const int CREATURE_HEALTH = 100;
    const int CREATURE_SPEED = 6;
    const int CREATURE_ROTATION_DEGREE = 30;
    const int CREATURE_EATING_VALUE = 10;

    const int FOOD_NUMBER_MIN = 20;
    const int FOOD_NUMBER_MAX = 40;
    const int FOOD_VALUE_MIN = 5;
    const int FOOD_VALUE_MAX = 20;
    const int FOOD_RADIUS = 20;

    const float EPSILON = 0.000001;
}
#endif