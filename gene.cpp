#include "gene.h"
#include "randomGen.h"
#include "tools.h"

namespace gene
{
    uint32_t generateRadomGene(int inputNumber, int internalNumber, int outputNumber)
    {
        uint32_t gene = RandomGen::getRandomInt(0, 0xFFFFFFFF);
        // we need to correct the ids of the sender and receiver according to their type
        return correctGene(gene, inputNumber, internalNumber, outputNumber);
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
}