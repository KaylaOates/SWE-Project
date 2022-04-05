#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include "TextBox.cpp"
#include "LinkLogger.h"
#include <SFML/Graphics.hpp>

int main(int argc, char* const argv[])
{
	
    //running test before anything happens
    //Make sure that you create the linkLogger instance before this line of code as it completely writes over the file, so all the data from before will be lost.
    int result = Catch::Session().run(argc, argv);
	
	    //declare all window, shape, text, font objects here
    sf::RenderWindow window(sf::VideoMode(1480, 1024), "Link Logger");

    //-----------------------------------------------------TEXT BOXES------------------------------------------------------------//

    sf::Font font;
    font.loadFromFile("Images/Raleway-Regular.ttf");

    bool takeInputURL = false;
    sf::String stringDisplayURL;
    sf::Text textDisplayURL;
    textDisplayURL.setFont(font);
    textDisplayURL.setCharacterSize(30);
    textDisplayURL.setFillColor(sf::Color::Black);
    textDisplayURL.setPosition(300, 330);
    textDisplayURL.setString("Insert URL");
    bool firstClickURL = true;

    bool takeInputD = false;
    sf::String stringDisplayD;
    sf::Text textDisplayD;
    textDisplayD.setFont(font);
    textDisplayD.setCharacterSize(30);
    textDisplayD.setFillColor(sf::Color::Black);
    textDisplayD.setPosition(300, 480);
    textDisplayD.setString("Description");
    bool firstClickD = true;

    bool takeInputP = false;
    sf::String stringDisplayP;
    sf::Text textDisplayP;
    textDisplayP.setFont(font);
    textDisplayP.setCharacterSize(30);
    textDisplayP.setFillColor(sf::Color::Black);
    textDisplayP.setPosition(300, 630);
    textDisplayP.setString("Password?");
    bool firstClickP = true;

    bool takeInputT = false;
    sf::String stringDisplayT;
    sf::Text textDisplayT;
    textDisplayT.setFont(font);
    textDisplayT.setCharacterSize(30);
    textDisplayT.setFillColor(sf::Color::Black);
    textDisplayT.setPosition(300, 780);
    textDisplayT.setString("Time");
    bool firstClickT = true;

    //-----------------------------------------------------IMAGE IMPORTS---------------------------------------------------------//

    ImportImage Background("Background", -58, -58);
    ImportImage NoLogoBackground("NoLogoBackground", -58, -58);
    ImportImage AddLink("AddLink", 520, 30);
    ImportImage ClickedAddLink("ClickedAddLink", 520, 30);
        bool CheckClickedAddLink = false;
    ImportImage CalendarView("CalendarView", 990, 30);
    ImportImage ClickedCalendarView("ClickedCalendarView", 990, 30);
        bool CheckClickedCalendarView = false;
    ImportImage ListView("ListView", 50, 30);
    ImportImage ClickedListView("ClickedListView", 50, 30);
        bool CheckClickedListView = false;
    ImportImage LinkAdressInsert("LinkAdressInsert", 220, 300);
    ImportImage Description("Description", 220, 450);
    ImportImage Password("Password", 220, 600);
    ImportImage Time("Time", 220, 750);
    ImportImage SaveUnclicked("SaveUnclicked", 600, 885);
    ImportImage SaveClicked("SaveClicked", 600, 885);
        bool CheckSaveClicked = false;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            
            sf::Vector2i mouseP = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (ListView.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                    {
                        CheckClickedListView = !CheckClickedListView;
                        CheckClickedAddLink = false;
                        CheckClickedCalendarView = false;
                    }
                    if (AddLink.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                    {
                        CheckClickedAddLink = !CheckClickedAddLink;
                        CheckClickedListView = false;
                        CheckClickedCalendarView = false;
                    }
                    if (CalendarView.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                    {
                        CheckClickedCalendarView = !CheckClickedCalendarView;
                        CheckClickedListView = false;
                        CheckClickedAddLink = false;
                    }
                    if (SaveClicked.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                    {
                        CheckSaveClicked = !CheckSaveClicked;
                    }

                    if (CheckClickedAddLink)
                    {
                        //IF IT IS NOT CLICKED
                        if (!LinkAdressInsert.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                            takeInputURL = false;
                        //IF THE SEARCH BAR IS CLICKED
                        else if (LinkAdressInsert.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputURL = true;
                            if (firstClickURL)
                            {
                                textDisplayURL.setString("");
                                firstClickURL = false;
                            }
                        }
                            

                        //IF IT IS NOT CLICKED, RESET THE SEARCH BAR
                        if (!Description.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                            takeInputD = false;
                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
                        else if (Description.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputD = true;
                            if (firstClickD)
                            {
                                textDisplayD.setString("");
                                firstClickD = false;
                            }
                        }

                        //IF IT IS NOT CLICKED, RESET THE SEARCH BAR
                        if (!Password.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                            takeInputP = false;
                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
                        else if (Password.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputP = true;
                            if (firstClickP)
                            {
                                textDisplayP.setString("");
                                firstClickP = false;
                            }
                        }

                        //IF IT IS NOT CLICKED, RESET THE SEARCH BAR
                        if (!Time.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                            takeInputT = false;
                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
                        else if (Time.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputT = true;
                            if (firstClickT)
                            {
                                textDisplayT.setString("");
                                firstClickT = false;
                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                if (takeInputURL == true)
                {
                    //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                    if (event.text.unicode >= 32 && event.text.unicode <= 127)
                    {
                        stringDisplayURL += event.text.unicode;
                        textDisplayURL.setString(stringDisplayURL);
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayURL.isEmpty())
                        {
                            stringDisplayURL.erase(stringDisplayURL.getSize() - 1, 1);
                            textDisplayURL.setString(stringDisplayURL);
                        }
                    }
                }
                //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                if (takeInputD == true)
                {
                    //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                    if (event.text.unicode >= 32 && event.text.unicode <= 127)
                    {
                        stringDisplayD += event.text.unicode;
                        textDisplayD.setString(stringDisplayD);
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayD.isEmpty())
                        {
                            stringDisplayD.erase(stringDisplayD.getSize() - 1, 1);
                            textDisplayD.setString(stringDisplayD);
                        }
                    }
                }
                //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                if (takeInputP == true)
                {
                    //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                    if (event.text.unicode >= 32 && event.text.unicode <= 127)
                    {
                        stringDisplayP += event.text.unicode;
                        textDisplayP.setString(stringDisplayP);
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayP.isEmpty())
                        {
                            stringDisplayP.erase(stringDisplayP.getSize() - 1, 1);
                            textDisplayP.setString(stringDisplayP);
                        }
                    }
                }
                //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                if (takeInputT == true)
                {
                    //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                    if (event.text.unicode >= 32 && event.text.unicode <= 127)
                    {
                        stringDisplayT += event.text.unicode;
                        textDisplayT.setString(stringDisplayT);
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayT.isEmpty())
                        {
                            stringDisplayT.erase(stringDisplayT.getSize() - 1, 1);
                            textDisplayT.setString(stringDisplayT);
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);


        if (CheckClickedListView || CheckClickedAddLink || CheckClickedCalendarView)
            window.draw(NoLogoBackground.getSprite());
        else
            window.draw(Background.getSprite());
        
        if(!CheckClickedListView)
            window.draw(ListView.getSprite());
        else
            window.draw(ClickedListView.getSprite());

        if (!CheckClickedAddLink)
            window.draw(AddLink.getSprite());
        else
        {
            window.draw(ClickedAddLink.getSprite());
            window.draw(LinkAdressInsert.getSprite());
            window.draw(Description.getSprite());
            window.draw(Password.getSprite());
            window.draw(Time.getSprite());

            if (CheckSaveClicked)
            {
                window.draw(SaveClicked.getSprite());

                //SAVE ALL THE INFO HERE

                textDisplayURL.setString("");
                textDisplayP.setString("");
                textDisplayT.setString("");
                textDisplayD.setString("");

                firstClickURL = true;
                firstClickP = true;
                firstClickT = true;
                firstClickD = true;

                textDisplayURL.setString("Insert URL");
                textDisplayP.setString("Password?");
                textDisplayT.setString("Time");
                textDisplayD.setString("Description");

                CheckSaveClicked = false;

            }
            else
                window.draw(SaveUnclicked.getSprite());
            
            window.draw(textDisplayURL);
            window.draw(textDisplayP);
            window.draw(textDisplayT);
            window.draw(textDisplayD);
        }

        if(!CheckClickedCalendarView)
            window.draw(CalendarView.getSprite());
        else
            window.draw(ClickedCalendarView.getSprite());


        window.display();
    }

    return 0;
}
