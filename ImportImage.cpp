#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class ImportImage 
{      
public:
    string name;
    sf::Texture Textures;
    sf::Sprite Sprites;

    ImportImage(string name, int x, int y)
    {
        name = name;
        Textures.loadFromFile("Images/" + name + ".png");
        Sprites.setTexture(Textures);
        Sprites.setPosition(sf::Vector2f(x, y));
    }

    sf::Sprite getSprite()
    {
        return Sprites;
    }
};