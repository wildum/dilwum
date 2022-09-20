#ifndef GENE
#define GENE

#include <stdint.h>
#include <vector>

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
    uint32_t correctGeneNoInternalLimit(uint32_t gene, int inputNumber, int outputNumber);
    uint32_t correctGene(uint32_t gene, int inputNumber, int internalNumber, int outputNumber);
    uint32_t generateSpecificConnectionGene(int senderType, int senderId, int receiverType, int receiverId, float weight);
    std::vector<uint32_t> correctGenome(const std::vector<uint32_t>& genome);
    std::vector<uint32_t> removeDuplicatedConnections(const std::vector<uint32_t>& genome);
}

#endif