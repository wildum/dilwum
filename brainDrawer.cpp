#include "brainDrawer.h"
#include "tools.h"
#include "randomGen.h"
#include "gene.h"
#include <iomanip>
#include <sstream>

#include <SFML/Graphics.hpp>

BrainDrawer::BrainDrawer()
{
    if (!m_font.loadFromFile("assets/arial.ttf"))
    {
        tools::log("cant load the font !");
        return;
    }
}

void BrainDrawer::drawRandomBrain()
{
    Brain brain{};
    drawBrain(brain);
}

void BrainDrawer::drawBrain(Brain& brain)
{
    auto genome = brain.getGenome();

    if (genome.size() < 2)
    {
        tools::log("brain is too small!");
        return;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "Brain");

    buildNodes(genome);
    tools::log("Number of nodes involved : " + std::to_string(m_nodes.size()));
    buildConnections(genome);
    tools::log("Number of connections involved : " + std::to_string(m_connections.size()));

    bool pressingMouseButton = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (!pressingMouseButton && event.type == sf::Event::MouseButtonPressed)
            {
                pressingMouseButton = true;
            }
            else if (pressingMouseButton && event.type == sf::Event::MouseButtonReleased)
            {
                pressingMouseButton = false;
            }
            if (pressingMouseButton)
            {
                onPressingMouseButton(event.mouseMove.x, event.mouseMove.y);
            }
        }
        window.clear(Config::getBACKGROUND_COLOR());
        drawConnections(window);
        drawNodes(window);
        window.display();
    }
}

void BrainDrawer::onPressingMouseButton(int x, int y)
{
    for (auto& node : m_nodes)
    {
        auto pos = node.shape.getPosition();
        if (tools::squaredDist(x, y, pos.x, pos.y) < node.shape.getRadius()*node.shape.getRadius())
        {
            node.text.setPosition(x - NODE_RADIUS / 2.0f, y - NODE_RADIUS / 2.0f);
            node.shape.setPosition(x, y);
            break;
        }
    }
}

void BrainDrawer::buildNodes(const std::vector<uint32_t>& genome)
{
    for (int i = 0; i < genome.size(); i++)
    {
        uint32_t gene = genome[i];
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;
        buildNode(senderType, senderId, ConnectionSide::SENDER);
        buildNode(receiverType, receiverId, ConnectionSide::RECEIVER);
    }
}

void BrainDrawer::buildConnections(const std::vector<uint32_t>& genome)
{
    for (int i = 0; i < genome.size(); i++) 
    {
        uint32_t gene = genome[i];
        int senderType = gene >> 31;
        int receiverType = (gene >> 23) & 1;
        int senderId = (gene >> 24) & 127;
        int receiverId = (gene >> 16) & 127;
        Connection connection;
        for (int j = 0; j < m_nodes.size(); j++)
        {
            if (m_nodes[j].id == senderId && ((m_nodes[j].type == NeuronType::INPUT && senderType == 1) || (m_nodes[j].type == NeuronType::INTERNAL && senderType == 0)))
            {
                connection.senderIndex = j;
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

        connection.text.setFont(m_font);
        connection.text.setCharacterSize(20);
        connection.text.setFillColor(sf::Color::Black);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) <<gene:: getWeightFromGene(gene);
        connection.text.setString(stream.str());
        m_connections.push_back(connection);
    }
}

void BrainDrawer::buildNode(int type, int id, ConnectionSide connectionSide)
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

        node.shape.setRadius(NODE_RADIUS);
        node.shape.setOrigin(NODE_RADIUS, NODE_RADIUS);

        switch (node.type)
        {
            case NeuronType::INPUT:
                node.shape.setPosition(RandomGen::getRandomInt(100, WINDOWX), RandomGen::getRandomInt(100, WINDOWY / 3));
                break;
            case NeuronType::INTERNAL:
                node.shape.setPosition(RandomGen::getRandomInt(100, WINDOWX), RandomGen::getRandomInt(WINDOWY / 3, (2 * WINDOWY) / 3));
                break;
            case NeuronType::OUTPUT:
                node.shape.setPosition(RandomGen::getRandomInt(100, WINDOWX), RandomGen::getRandomInt((2 * WINDOWY) / 3, WINDOWY - 100));
                break;
            default:
                break;
        }
        node.text.setFont(m_font);
        node.text.setCharacterSize(20);
        node.text.setFillColor(sf::Color::Black);
        node.text.setPosition(node.shape.getPosition().x - NODE_RADIUS / 2.0f, node.shape.getPosition().y - NODE_RADIUS / 2.0f);
        switch (node.type)
        {
            case NeuronType::INPUT:
                node.shape.setFillColor(sf::Color::Blue);
                node.text.setString(INPUT_NAMES[id]);
                break;
            case NeuronType::OUTPUT:
                node.shape.setFillColor(sf::Color::Red);
                node.text.setString(OUTPUT_NAMES[id]);
                break;
            case NeuronType::INTERNAL:
                node.shape.setFillColor(sf::Color::Yellow);
                node.text.setString("N" + std::to_string(m_internalNodeCounter++));
                break;
        }
        m_nodes.push_back(node);
    }
}

void BrainDrawer::drawNodes(sf::RenderWindow& window)
{
    for (const auto& node : m_nodes)
    {
        window.draw(node.shape);
        window.draw(node.text);
    }
}

void BrainDrawer::drawConnections(sf::RenderWindow& window)
{
    for (auto& connection : m_connections)
    {
        if (connection.receiverIndex == connection.senderIndex)
        {
            sf::Vector2f position = m_nodes[connection.receiverIndex].shape.getPosition();
            connection.selfConnection.setRadius(20);
            connection.selfConnection.setOutlineColor(sf::Color::Black);
            connection.selfConnection.setOutlineThickness(2);
            connection.selfConnection.setPosition(position);
            connection.selfConnection.setFillColor(sf::Color::Transparent);
            window.draw(connection.selfConnection);
            connection.text.setPosition(position.x + 3, position.y + 3);
            window.draw(connection.text);
        }
        else
        {
            sf::Vector2f senderPosition = m_nodes[connection.senderIndex].shape.getPosition();
            sf::Vector2f receiverPosition = m_nodes[connection.receiverIndex].shape.getPosition();
            connection.line[0].position = senderPosition;
            connection.line[1].position = receiverPosition;
            window.draw(connection.line, 2, sf::Lines);
            Vec v{receiverPosition.x - senderPosition.x, receiverPosition.y - senderPosition.y};
            v.normalize();
            v.scale(tools::dist(senderPosition.x, senderPosition.y, receiverPosition.x, receiverPosition.y) - NODE_RADIUS - ARROW_RADIUS);
            sf::CircleShape arrow(80, 3);
            arrow.setRadius(ARROW_RADIUS);
            arrow.setFillColor(sf::Color::Black);
            arrow.setOrigin(ARROW_RADIUS, ARROW_RADIUS);
            arrow.setPosition(senderPosition.x + v.x, senderPosition.y + v.y);
            arrow.setRotation(tools::radianToDegrees(atan2(receiverPosition.x - senderPosition.x, senderPosition.y - receiverPosition.y)));
            window.draw(arrow);
            connection.text.setPosition((senderPosition.x + receiverPosition.x) / 2.0f, (senderPosition.y + receiverPosition.y) / 2.0f);
            window.draw(connection.text);
        }
    }
}