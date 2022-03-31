#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include "LinkLogger.h"
#include <SFML/Graphics.hpp>

int main(int argc, char* const argv[])
{
	
    //running test before anything happens
    //Make sure that you create the linkLogger instance before this line of code as it completely writes over the file, so all the data from before will be lost.
    int result = Catch::Session().run(argc, argv);
    
    
    {
        //declare all window, shape, text, font objects here
        sf::RenderWindow window(sf::VideoMode(1480, 1024), "Link Logger");

        while (window.isOpen())
        {
            sf::Event event;
            //this while loop is where you will check for events, like checking for a box to be left clicked, right clicked, check for typing to happen ect.
            //If anyone is making a textbox that the user will write into ask me for help because I have a code for how to do that really easily - Devesh

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            //SFML should alwasy have a clear, draw, display statement set here. Clear will clear the screen of previous elements, draw will draw what needs to be drawn to the screen
            //display will display it to the screen. If you need to change what is being shown on the screen, change what is being drawn to the screen
            window.clear(sf::Color::White);
            //DRAW STATEMENTS GOES HERE
            // window.draw(/*thing to be draw to the screen goes here */);
            window.display();
        }

        return 0;
    }

	return 0;
}