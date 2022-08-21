#ifndef NEURON
#define NEURON

namespace neuron
{
    const int OUTPUT_NUMBER = 5;
    const int INPUT_NUMBER = 4;
}

enum Taste
{
    TASTE_NOTHING, TASTE_FOOD
};

const int ANTENNATOUCH_MAX_VALUE = 3;
enum AntennaTouch
{
    TOUCH_NOTHING, TOUCH_FOOD, TOUCH_CREATURE, TOUCH_WALL  
};

enum ConnectionSide
{
    SENDER, RECEIVER
};

enum NeuronType
{
    INPUT, INTERNAL, OUTPUT
};

enum Output
{
    ROTATE_LEFT, ROTATE_RIGHT, MOVE_FORWARD, WAIT, EAT
};

enum Input
{
    HEALTH, TASTE, LEFT_ANTENNA_TOUCH, RIGHT_ANTENNA_TOUCH
};

#endif