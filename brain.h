#ifndef BRAIN
#define BRAIN

#include <array>
#include <vector>
#include "neuron.h"
#include "config.h"

class Brain
{
    public:
        Brain();
        Brain(std::array<uint32_t, config::DNA_SIZE> dna);
};

#endif