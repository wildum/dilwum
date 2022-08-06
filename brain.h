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
        const std::vector<uint32_t>& getGenome() const {return m_genome;}
    private:
        std::vector<uint32_t> m_genome;
        int m_internalNeuronsNumber;
        int m_connectionsNumber;

        void generateGENOME();
        void buildBrain();
};

#endif