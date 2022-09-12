#include "brain.h"
#include "gene.h"
#include "randomGen.h"
#include "tools.h"
#include <limits>

#include <unordered_set>

Brain::Brain()
{
    generateGENOME();
    buildBrain();
}

Brain::Brain(const std::vector<uint32_t>& genome)
{
    m_genome = genome;
    buildBrain();
}

void Brain::generateGENOME()
{
    // first gene codes for the number of internal neurons and for the number of connections - total used : 16 bits
    uint32_t firstGene = RandomGen::getRandomInt(0, 65535);
    uint32_t connectionsNumber = tools::map(firstGene & 255, 255, config::GENOME_SIZE_MAX);
    m_internalNeuronsNumber = tools::map(firstGene >> 8, 255, config::INTERNAL_NEURON_NUMBER_MAX);
    // make sure that the output is connected?
    // dont put the original gene
    // m_genome.push_back(m_connectionsNumber | m_internalNeuronsNumber << 8);
    for (int i = 0; i < connectionsNumber; i++)
    {
        m_genome.push_back(gene::generateRadomGene(neuron::INPUT_NUMBER, m_internalNeuronsNumber, neuron::OUTPUT_NUMBER));
    }
}

void Brain::buildBrain()
{
    buildNodes();
    buildConnections();
    sortConnections();
}

void Brain::buildNodes()
{
    for (int i = 0; i < m_genome.size(); i++)
    {
        uint32_t gene = m_genome[i];
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;
        buildNode(senderType, senderId, ConnectionSide::SENDER);
        buildNode(receiverType, receiverId, ConnectionSide::RECEIVER);
    }
}

void Brain::setHealth(int health)
{
    m_inputValues[Input::HEALTH] = (float) health / config::CREATURE_HEALTH;
}

void Brain::setTaste(Taste taste)
{
    m_inputValues[Input::TASTE] = taste == TASTE_FOOD ? 1.0 : 0.0;
}

void Brain::setLeftAntennaTouch(AntennaTouch leftTouch)
{
    m_inputValues[Input::LEFT_ANTENNA_TOUCH] = (float) leftTouch / ANTENNATOUCH_MAX_VALUE;
}

void Brain::setRightAntennaTouch(AntennaTouch rightTouch)
{
    m_inputValues[Input::RIGHT_ANTENNA_TOUCH] = (float) rightTouch / ANTENNATOUCH_MAX_VALUE;
}

void Brain::process()
{
    for (const auto& connection : m_connections)
    {
        float outputValue = 0;
        if (m_nodes[connection.senderIndex].type == NeuronType::INPUT)
        {
            outputValue = m_inputValues[(Input) m_nodes[connection.senderIndex].id];
        }
        else
        {
            for (float values : m_nodes[connection.senderIndex].inputs)
                outputValue += values;
            outputValue = tanh(outputValue);
        }

        // if the nodes was triggered, it should clear its state before receiving new data
        if (m_nodes[connection.receiverIndex].triggered)
        {
            m_nodes[connection.receiverIndex].triggered = false;
            m_nodes[connection.receiverIndex].inputs.clear();
        }

        m_nodes[connection.receiverIndex].inputs.push_back(outputValue * connection.weight);
    }
}

Output Brain::pickAction()
{
    Output action;
    float bestScore = std::numeric_limits<float>::min();

    for (const auto& node : m_nodes)
    {
        if (node.type == NeuronType::OUTPUT)
        {
            float score = 0;
            for (float values : node.inputs)
                score += values;
            score = tanh(score);
            if (score > bestScore)
            {
                bestScore = score;
                action = static_cast<Output>(node.id);
            }
        }
    }

    return action;
}

void Brain::buildConnections()
{
    for (int i = 0; i < m_genome.size(); i++) 
    {
        uint32_t gene = m_genome[i];
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;
        Connection connection;
        connection.id = i;
        connection.weight = getWeightFromGene(gene);
        for (int j = 0; j < m_nodes.size(); j++)
        {
            if (m_nodes[j].id == senderId && ((m_nodes[j].type == NeuronType::INPUT && senderType == 1) || (m_nodes[j].type == NeuronType::INTERNAL && senderType == 0)))
            {
                connection.senderIndex = j;
                if (m_nodes[j].type == NeuronType::INPUT)
                {
                    connection.connectedToInput = true;
                }
            }
            if (m_nodes[j].id == receiverId && ((m_nodes[j].type == NeuronType::OUTPUT && receiverType == 1) || (m_nodes[j].type == NeuronType::INTERNAL && receiverType == 0)))
            {
                connection.receiverIndex = j;
            }
        }

        if (connection.senderIndex == -1 || connection.receiverIndex == -1)
        {
            tools::log("broken connection");
            std::cout << senderType << " " << receiverType << " " << senderId << " " << receiverId << " " << connection.senderIndex << " " << connection.receiverIndex << std::endl;
            continue;
        }
        m_connections.push_back(connection);
    }
}

float Brain::getWeightFromGene(uint32_t gene)
{
    return ((gene & 65535) - 32767.5) / 8192; // weight is set between -4 and 4
}

void Brain::buildNode(int type, int id, ConnectionSide connectionSide)
{
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(), [connectionSide, type, id](const Node& node){
        bool sameSide = false;
        if (connectionSide == ConnectionSide::RECEIVER)
        {
            sameSide = type == 0 && node.type == NeuronType::INTERNAL || type == 1 && node.type == NeuronType::OUTPUT;
        }
        else
        {
            sameSide = type == 0 && node.type == NeuronType::INTERNAL || type == 1 && node.type == NeuronType::INPUT;
        }
        return sameSide && id == node.id;
    });
    if (it == m_nodes.end())
    {
        Node node;
        node.id = id;
        if (connectionSide == ConnectionSide::RECEIVER)
        {
            node.type = type == 0 ? NeuronType::INTERNAL : NeuronType::OUTPUT;
        }
        else if (connectionSide == ConnectionSide::SENDER)
        {
            node.type = type == 0 ? NeuronType::INTERNAL : NeuronType::INPUT;
        }
        m_nodes.push_back(node);
    }
}

void Brain::sortConnections()
{
    std::unordered_set<int> connectionIdsClosed;
    std::unordered_set<int> nodeIdsClosed;
    std::vector<Connection> sortedConnections;
    std::vector<int> nextNeuronIds;

    for (const auto& connection : m_connections)
    {
        if (connection.connectedToInput)
        {
            sortedConnections.push_back(connection);
            nextNeuronIds.push_back(connection.receiverIndex);
            connectionIdsClosed.insert(connection.id);
            nodeIdsClosed.insert(connection.senderIndex);
        }
    }

    int timeoutInterations = 10000;
    int iter = 0;
    while (sortedConnections.size() != m_connections.size())
    {
        int canditateIndex = 0;
        int missingConnections = 999;
        for (int i = 0; i < m_nodes.size(); i++)
        {
            if (nodeIdsClosed.find(i) == nodeIdsClosed.end())
            {
                int currentMissingConnections = 0;
                for (const auto& connection : m_connections)
                {
                    if (connection.receiverIndex == i && connectionIdsClosed.find(connection.id) == connectionIdsClosed.end())
                    {
                        currentMissingConnections++;
                    }
                }
                if (currentMissingConnections < missingConnections)
                {
                    missingConnections = currentMissingConnections;
                    canditateIndex = i;
                }
            }
        }

        nodeIdsClosed.insert(canditateIndex);

        for (const auto& connection : m_connections)
        {
            if (connection.senderIndex == canditateIndex)
            {
                connectionIdsClosed.insert(connection.id);
                sortedConnections.push_back(connection);
            }
        }
        iter++;
        if (iter > timeoutInterations)
        {
            tools::log("something went badly wrong here");
            break;
        }
    }
    m_connections = sortedConnections;
}