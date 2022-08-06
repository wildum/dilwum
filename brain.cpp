#include "brain.h"
#include "gene.h"
#include "randomGen.h"
#include "tools.h"

Brain::Brain()
{
    generateGENOME();
    buildBrain();
}

void Brain::generateGENOME()
{
    // first gene codes for the number of internal neurons and for the number of connections - total used : 16 bits
    uint32_t firstGene = RandomGen::getRandomInt(0, 65535);
    m_connectionsNumber = tools::map(firstGene & 255, 255, config::GENOME_SIZE_MAX);
    m_internalNeuronsNumber = tools::map(firstGene >> 8, 255, config::INTERNAL_NEURON_NUMBER_MAX);
    // make sure that the output is connected?
    m_genome.push_back(m_connectionsNumber | m_internalNeuronsNumber << 8);
    for (int i = 0; i < m_connectionsNumber; i++)
    {
        m_genome.push_back(gene::generateRadomGene(neuron::INPUT_NUMBER, m_internalNeuronsNumber, neuron::OUTPUT_NUMBER));
    }
}

void Brain::buildBrain()
{

}