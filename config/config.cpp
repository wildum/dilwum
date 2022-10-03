#include "config.h"
#include <fstream>
#include "../../NLOHMANN_JSON/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

float Config::TURN_TIME_SECOND;
int Config::GENOME_SIZE_MAX; // max 8 bits
int Config::INTERNAL_NEURON_NUMBER_MAX; // max 8 bits
int Config::GENERATIONS;
float Config::GA_POP_RETAINED_RATIO;
float Config::GA_MUTATION_RATE_MIN;
float Config::GA_MUTATION_RATE_MAX;
int Config::MAP_WIDTH;
int Config::MAP_HEIGHT;
int Config::GAME_TURN;
int Config::POP_NUMBER;
int Config::CREATURE_RADIUS;
int Config::CREATURE_HEALTH;
int Config::CREATURE_SPEED;
int Config::CREATURE_ROTATION_DEGREE;
int Config::CREATURE_EATING_VALUE;
int Config::CREATURE_ANTENNA_ANGLE;
int Config::CREATURE_ANTENNA_LENGTH_FROM_BODY;
int Config::FOOD_NUMBER_MIN;
int Config::FOOD_NUMBER_MAX;
int Config::FOOD_VALUE_MIN;
int Config::FOOD_VALUE_MAX;
int Config::FOOD_RADIUS;
sf::Color Config::BACKGROUND_COLOR;
sf::Color Config::FOOD_COLOR;
constexpr float Config::EPSILON;

void Config::readConfig(std::string& path)
{
    std::ifstream file(path, std::ifstream::binary);
    json data = json::parse(file);

    TURN_TIME_SECOND = data["turnTimeSecond"];
    GENOME_SIZE_MAX = data["genomeMaxSize"]; // max 8 bits
    INTERNAL_NEURON_NUMBER_MAX = data["internalNeuronNumberMax"]; // max 8 bits
    GENERATIONS = data["ga"]["gen"];
    GA_POP_RETAINED_RATIO = data["ga"]["popRetainedRatio"];
    GA_MUTATION_RATE_MIN = data["ga"]["mutationRateMin"];
    GA_MUTATION_RATE_MAX = data["ga"]["mutationRateMax"];
    MAP_WIDTH = data["map"]["width"];
    MAP_HEIGHT = data["map"]["height"];
    GAME_TURN = data["gameTurn"];
    POP_NUMBER = data["popNumber"];
    CREATURE_RADIUS = data["creature"]["radius"];
    CREATURE_HEALTH = data["creature"]["health"];
    CREATURE_SPEED = data["creature"]["speed"];
    CREATURE_ROTATION_DEGREE =data["creature"]["rotationDegree"];
    CREATURE_EATING_VALUE = data["creature"]["eatingValue"];
    CREATURE_ANTENNA_ANGLE = data["creature"]["antennaAngle"];
    CREATURE_ANTENNA_LENGTH_FROM_BODY = data["creature"]["antennaLengthFromBody"];
    FOOD_NUMBER_MIN = data["food"]["numberMin"];
    FOOD_NUMBER_MAX = data["food"]["numberMax"];
    FOOD_VALUE_MIN = data["food"]["valueMin"];
    FOOD_VALUE_MAX = data["food"]["valueMax"];
    FOOD_RADIUS = data["food"]["radius"];
    auto colorArrayBackground = data["color"]["background"];
    BACKGROUND_COLOR = {colorArrayBackground[0], colorArrayBackground[1], colorArrayBackground[2]};
    auto colorArrayFood = data["color"]["food"];
    FOOD_COLOR = {colorArrayFood[0], colorArrayFood[1], colorArrayFood[2]};
}