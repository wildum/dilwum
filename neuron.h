namespace neuron
{
    const int OUTPUT_NUMBER = 5;
    const int INPUT_NUMBER = 2;
}

enum NeuronType
{
    INPUT, NEUTRAL, OUTPUT
};

enum Output
{
    ROTATE_LEFT, ROTATE_RIGHT, MOVE_FORWARD, WAIT, EAT
};

enum Input
{
    HEALTH, EYE
};