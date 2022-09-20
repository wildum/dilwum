#include "gene.h"
#include "randomGen.h"
#include "tools.h"
#include <unordered_set>

namespace gene
{
    uint32_t generateRadomGene(int inputNumber, int internalNumber, int outputNumber)
    {
        uint32_t gene = RandomGen::getRandomInt(0, 0xFFFFFFFF);
        // we need to correct the ids of the sender and receiver according to their type
        return correctGene(gene, inputNumber, internalNumber, outputNumber);
    }

    uint32_t correctGeneNoInternalLimit(uint32_t gene, int inputNumber, int outputNumber)
    {
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;

        if (senderType == SenderType::SENDER_INPUT)
            senderId = tools::map(senderId, 127, inputNumber-1);

        if (receiverType == ReceiverType::RECEIVER_OUTPUT)
            receiverId = tools::map(receiverId, 127, outputNumber-1);

        return (senderType << 31) | (senderId << 24) | (receiverType << 23) | (receiverId << 16) | (gene & 65535);
    }

    uint32_t correctGene(uint32_t gene, int inputNumber, int internalNumber, int outputNumber)
    {
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;

        if (senderType == SenderType::SENDER_INTERNAL)
            senderId = tools::map(senderId, 127, internalNumber-1);
        else
            senderId = tools::map(senderId, 127, inputNumber-1);

        if (receiverType == ReceiverType::RECEIVER_INTERNAL)
            receiverId = tools::map(receiverId, 127, internalNumber-1);
        else
            receiverId = tools::map(receiverId, 127, outputNumber-1);

        return (senderType << 31) | (senderId << 24) | (receiverType << 23) | (receiverId << 16) | (gene & 65535);
    }

    uint32_t generateSpecificConnectionGene(int senderType, int senderId, int receiverType, int receiverId, float weight)
    {
        uint32_t gene = 0;
        int encodedWeight = weight * 8192 + 32767.5;
        gene += encodedWeight;
        return (senderType << 31) | (senderId << 24) | (receiverType << 23) | (receiverId << 16) | (gene & 65535);
    }

    std::vector<uint32_t> correctGenome(const std::vector<uint32_t>& genome)
    {
        std::vector<uint32_t> correctedGenome = removeDuplicatedConnections(genome);
        return correctedGenome;
    }

    std::vector<uint32_t> removeDuplicatedConnections(const std::vector<uint32_t>& genome)
    {
        std::vector<uint32_t> correctedGenome;

        std::unordered_set<uint32_t> connectionSet;
        for (const auto& gene : genome)
        {
            uint32_t connection = ((gene >> 31) << 31) | (((gene >> 24) & 127) << 24) | (((gene >> 23) & 1) << 23) | (((gene >> 16) & 127) << 16);
            if (connectionSet.find(connection) == connectionSet.end())
            {
                connectionSet.insert(connection);
                correctedGenome.push_back(gene);
            }
        }
        return correctedGenome;
    }
}