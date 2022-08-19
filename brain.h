#ifndef BRAIN
#define BRAIN

#include <array>
#include <vector>
#include "neuron.h"
#include "config.h"

struct Node
{
    NeuronType type;
    int id;
    bool visitedOnce = false;
    std::vector<float> inputs; // empty the vector when sending values out
};

struct Connection
{
    int senderIndex = -1;
    int receiverIndex = -1;
    int id;
    float weight;
    bool connectedToInput = false;
};

class Brain
{
    public:
        Brain();
        const std::vector<uint32_t>& getGenome() const {return m_genome;}
        const std::vector<Connection>& getConnection() const{return m_connections;}
    private:
        std::vector<uint32_t> m_genome;
        std::vector<Node> m_nodes;
        std::vector<Connection> m_connections;
        int m_internalNeuronsNumber;
        int m_connectionsNumber;

        void generateGENOME();
        void buildBrain();
        void buildNode(int type, int id, ConnectionSide connectionSide);
        void buildConnections();
        void buildNodes();
        void sortConnections();
        float getWeightFromGene(uint32_t gene);
};

#endif