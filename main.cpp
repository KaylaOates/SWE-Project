#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include "LinkLogger.h"
#include <SFML/Graphics.hpp>

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);
    {
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
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

        return 0;
    }

	return 0;
}