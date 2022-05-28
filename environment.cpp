#include "environment.h"
#include "game.h"
#include "randomGen.h"
#include "frame.h"

#include <SFML/Graphics.hpp>

void Environment::initialize()
{
    RandomGen::initialize();
}

void Environment::run()
{
    initialize();

    Game game;

    std::vector<Frame> frames;
    bool recordRun = true;
    game.run(frames, recordRun);

    if (recordRun && !frames.empty())
    {
        sf::RenderWindow window(sf::VideoMode(2000, 1000), "BSS");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        sf::Clock deltaClock;

        while (window.isOpen())
        {
            sf::Int32 dt = deltaClock.restart().asMilliseconds();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }
    }
}