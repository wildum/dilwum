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
    bool triggered = false;
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
        Brain(const std::vector<uint32_t>& genome);
        std::vector<uint32_t>& getGenome() {return m_genome;}
        const std::vector<Connection>& getConnection() const {return m_connections;}
        const int getInternalNeuronsNumber() const {return m_internalNeuronsNumber;}
        void setHealth(int health);
        void setTaste(Taste taste);
        void setLeftAntennaTouch(AntennaTouch leftTouch);
        void setRightAntennaTouch(AntennaTouch rightTouch);
        void process();
        void setInternalNeuronNumber(int internalNeuronNumber) {m_internalNeuronsNumber = internalNeuronNumber;}
        Output pickAction();

    private:
        std::vector<uint32_t> m_genome;
        std::vector<Node> m_nodes;
        std::vector<Connection> m_connections;
        int m_internalNeuronsNumber;

        void generateGENOME();
        void buildBrain();
        void buildNode(int type, int id, ConnectionSide connectionSide);
        void buildConnections();
        void buildNodes();
        void sortConnections();
        float getWeightFromGene(uint32_t gene);

        std::map<Input, float> m_inputValues;
};

#endif