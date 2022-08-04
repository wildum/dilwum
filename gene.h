#ifndef GENE
#define GENE

#include <stdint.h>

namespace gene
{
    enum SenderType
    {
        SENDER_NEUTRAL, SENDER_INPUT
    };
    enum ReceiverType
    {
        RECEIVER_NEUTRAL, RECEIVER_OUTPUT
    };
    uint32_t generateRadomGene(int inputNumber, int neutralNumber, int outputNumber);
    uint32_t correctGene(uint32_t gene, int inputNumber, int neutralNumber, int outputNumber);
}

#endif