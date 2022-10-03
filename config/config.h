#ifndef CONFIG
#define CONFIG

#include <SFML/Graphics.hpp>

class Config
{
    public:
        void static readConfig(std::string& path);
        static float getTURN_TIME_SECOND() {return TURN_TIME_SECOND;}
        static int getGENOME_SIZE_MAX() {return GENOME_SIZE_MAX;}
        static int getINTERNAL_NEURON_NUMBER_MAX() {return INTERNAL_NEURON_NUMBER_MAX;}
        static int getGENERATIONS() {return GENERATIONS;}
        static float getGA_POP_RETAINED_RATIO() {return GA_POP_RETAINED_RATIO;}
        static float getGA_MUTATION_RATE_MIN() {return GA_MUTATION_RATE_MIN;}
        static float getGA_MUTATION_RATE_MAX() {return GA_MUTATION_RATE_MAX;}
        static int getMAP_WIDTH() {return MAP_WIDTH;}
        static int getMAP_HEIGHT() {return MAP_HEIGHT;}
        static int getGAME_TURN() {return GAME_TURN;}
        static int getPOP_NUMBER() {return POP_NUMBER;}
        static int getCREATURE_RADIUS() {return CREATURE_RADIUS;}
        static int getCREATURE_HEALTH() {return CREATURE_HEALTH;}
        static int getCREATURE_SPEED() {return CREATURE_SPEED;}
        static int getCREATURE_ROTATION_DEGREE() {return CREATURE_ROTATION_DEGREE;}
        static int getCREATURE_EATING_VALUE() {return CREATURE_EATING_VALUE;}
        static int getCREATURE_ANTENNA_ANGLE() {return CREATURE_ANTENNA_ANGLE;}
        static int getCREATURE_ANTENNA_LENGTH_FROM_BODY() {return CREATURE_ANTENNA_LENGTH_FROM_BODY;}
        static int getFOOD_NUMBER_MIN() {return FOOD_NUMBER_MIN;}
        static int getFOOD_NUMBER_MAX() {return FOOD_NUMBER_MAX;}
        static int getFOOD_VALUE_MIN() {return FOOD_VALUE_MIN;}
        static int getFOOD_VALUE_MAX() {return FOOD_VALUE_MAX;}
        static int getFOOD_RADIUS() {return FOOD_RADIUS;}
        static sf::Color getBACKGROUND_COLOR() {return BACKGROUND_COLOR;}
        static sf::Color getFOOD_COLOR() {return FOOD_COLOR;}
        static float getEPSILON() {return EPSILON;}
    private:
        static float TURN_TIME_SECOND;
        static int GENOME_SIZE_MAX; // max 8 bits
        static int INTERNAL_NEURON_NUMBER_MAX; // max 8 bits
        static int GENERATIONS;
        static float GA_POP_RETAINED_RATIO;
        static float GA_MUTATION_RATE_MIN;
        static float GA_MUTATION_RATE_MAX;
        static int MAP_WIDTH;
        static int MAP_HEIGHT;
        static int GAME_TURN;
        static int POP_NUMBER;
        static int CREATURE_RADIUS;
        static int CREATURE_HEALTH;
        static int CREATURE_SPEED;
        static int CREATURE_ROTATION_DEGREE;
        static int CREATURE_EATING_VALUE;
        static int CREATURE_ANTENNA_ANGLE;
        static int CREATURE_ANTENNA_LENGTH_FROM_BODY;
        static int FOOD_NUMBER_MIN;
        static int FOOD_NUMBER_MAX;
        static int FOOD_VALUE_MIN;
        static int FOOD_VALUE_MAX;
        static int FOOD_RADIUS;
        static sf::Color BACKGROUND_COLOR;
        static sf::Color FOOD_COLOR;
        static constexpr float EPSILON = 0.000001;
};
#endif