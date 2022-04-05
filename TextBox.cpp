#include "ImportImage.cpp"

class TextBox
{
public:
    bool takeInput;
    sf::String stringDisplay;
    sf::Text textDisplay;
    int x;
    int y;

    TextBox(int x, int y)
    {
        takeInput = false;
        stringDisplay = "";

        sf::Font font;
        font.loadFromFile("Images/Raleway-Regular.ttf");

        textDisplay.setFont(font);
        textDisplay.setFillColor(sf::Color::Black);
        textDisplay.setPosition(sf::Vector2f(x, y));
        textDisplay.setCharacterSize(30);
    }

    void textBoxClicked(sf::Sprite Sprites, sf::Vector2i mouseP)
    {

    }

    void keysClicked(sf::Event event)
    {

    }

    sf::Text getTextDisplay()
    {
        return textDisplay;
    }
};