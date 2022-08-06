#ifndef GENE
#define GENE

#include <stdint.h>

namespace gene
{
    enum SenderType
    {
        SENDER_INTERNAL, SENDER_INPUT
    };
    enum ReceiverType
    {
        RECEIVER_INTERNAL, RECEIVER_OUTPUT
    };
    uint32_t generateRadomGene(int inputNumber, int internalNumber, int outputNumber);
    uint32_t correctGene(uint32_t gene, int inputNumber, int internalNumber, int outputNumber);
}

#endif