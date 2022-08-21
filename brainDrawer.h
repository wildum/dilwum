#ifndef BRAIN_DRAWER
#define BRAIN_DRAWER

#include "brain.h"
#include "vec.h"
#include "neuron.h"

#include <array>

class BrainDrawer
{
    public:
        BrainDrawer();
        void drawRandomBrain();
        void drawBrain(const Brain& brain);

    private:

        sf::Font m_font;

        const int WINDOWX = 2000;
        const int WINDOWY = 1000;

        const std::array<std::string, 4> INPUT_NAMES {{"H", "T", "LA", "RA"}};
        const std::array<std::string, 5> OUTPUT_NAMES {{"RL", "RR", "MF", "W", "E"}};

        struct Node
        {
            NeuronType type;
            int id;
            sf::CircleShape shape;
            sf::Text text;
        };

        struct Connection
        {
            int senderIndex = -1;
            int receiverIndex = -1;
            sf::Vertex line[2] = {sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black), sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black)};
            sf::CircleShape selfConnection;
            sf::Text text;
        };

        const int NODE_RADIUS = 20;
        const int ARROW_RADIUS = 10;

        int m_internalNodeCounter = 0;
        std::vector<Node> m_nodes;
        std::vector<Connection> m_connections;
        void buildNodes(const std::vector<uint32_t>& genome);
        void buildNode(int type, int id, ConnectionSide connectionSide);
        void buildConnections(const std::vector<uint32_t>& genome);
        void drawNodes(sf::RenderWindow& window);
        void drawConnections(sf::RenderWindow& window);
        void onPressingMouseButton(int x, int y);
};

#endif