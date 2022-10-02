#ifndef BRAIN
#define BRAIN

#include <array>
#include <vector>
#include "neuron.h"
#include "config/config.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

struct Node
{
    NeuronType type;
    int id;
    bool triggered = false;
    std::vector<float> inputs; // empty the vector when sending values out

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & type;
        ar & triggered;
        ar & id;
        ar & inputs;
    }
};

struct Connection
{
    int senderIndex = -1;
    int receiverIndex = -1;
    int id;
    float weight;
    bool connectedToInput = false;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & senderIndex;
        ar & receiverIndex;
        ar & id;
        ar & weight;
        ar & connectedToInput;
    }
};

class Brain
{
    public:
        Brain();
        Brain(const std::vector<uint32_t>& genome);
        void buildBrain();
        std::vector<uint32_t>& getGenome() {return m_genome;}
        const std::vector<Connection>& getConnection() const {return m_connections;}
        void setGenome(std::vector<uint32_t>&& genome) {m_genome = genome;}
        void setHealth(int health);
        void setTaste(Taste taste);
        void setLeftAntennaTouch(AntennaTouch leftTouch);
        void setRightAntennaTouch(AntennaTouch rightTouch);
        float getTaste() {return m_inputValues[TASTE];}
        void process();
        Output pickAction();

    private:
        std::vector<uint32_t> m_genome;
        std::vector<Node> m_nodes;
        std::vector<Connection> m_connections;

        void resetBrain();
        void generateGenome();
        void buildNode(int type, int id, ConnectionSide connectionSide);
        void buildConnections();
        void buildNodes();
        void sortConnections();
        float getWeightFromGene(uint32_t gene);

        std::map<Input, float> m_inputValues;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_genome;
            ar & m_nodes;
            ar & m_connections;
            ar & m_inputValues;
        }
};

#endif