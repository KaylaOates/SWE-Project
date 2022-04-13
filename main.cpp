#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include "TextBox.cpp"
#include "LinkLogger.h"
#include "functions.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h> 
///////////////////////////////////TODO: MAKE SURE THE CSV WRITING WORKS PROPERLY AND THE LINKLOGGER GRABS THE MEETINGS IN THE CSV AND ADDS THEM TO ITS VECTOR IN THE CONSTRUCTOR.////////////////////////////////////////////////////////


int main(int argc, char* const argv[])
{
	

	
	//declare all window, shape, text, font objects here
    sf::RenderWindow window;
    sf::RenderWindow userWindow(sf::VideoMode(600, 480), "Select User Profile");
    bool userBoxOpen = true;
    linkLogger tempLinkLogger = linkLogger();
    linkLogger* meetingList = &tempLinkLogger;

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
    int textTrackerURL = 0;

    bool takeInputD = false;
    sf::String stringDisplayD;
    sf::Text textDisplayD;
    textDisplayD.setFont(font);
    textDisplayD.setCharacterSize(30);
    textDisplayD.setFillColor(sf::Color::Black);
    textDisplayD.setPosition(300, 480);
    textDisplayD.setString("Description");
    bool firstClickD = true;
    int textTrackerD = 0;

    bool takeInputP = false;
    sf::String stringDisplayP;
    sf::Text textDisplayP;
    textDisplayP.setFont(font);
    textDisplayP.setCharacterSize(30);
    textDisplayP.setFillColor(sf::Color::Black);
    textDisplayP.setPosition(300, 630);
    textDisplayP.setString("Password?");
    bool firstClickP = true;
    int textTrackerP = 0;

    bool takeInputT = false;
    sf::String stringDisplayT;
    sf::Text textDisplayT;
    textDisplayT.setFont(font);
    textDisplayT.setCharacterSize(30);
    textDisplayT.setFillColor(sf::Color::Black);
    textDisplayT.setPosition(300, 780);
    textDisplayT.setString("Time");
    bool firstClickT = true;
    int textTrackerT = 0;


    sf::String stringDisplayU;
    sf::Text textDisplayU;
    bool takeInputU = false;
    textDisplayU.setFont(font);
    textDisplayU.setCharacterSize(30);
    textDisplayU.setFillColor(sf::Color::Black);
    textDisplayU.setPosition(70, 128);
    textDisplayU.setString("User Profile Name");
    bool firstClickU = true;

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

    ImportImage userBox("UsersB", 40, 100);
    ImportImage SaveClicked2("SaveUnclicked", 170, 250);
    string userProfParameter;
    bool saveClicked2U = false;
    
    
    
    
    //---------------------------------------------------------------MAIN PROGRAM LOOP-------------------------------------------------------------------//
    bool testRan = false;
    int textTracker = 0;

    while (window.isOpen() || userWindow.isOpen())
    {
        sf::Event event;
        if (userBoxOpen)
        {
            while (userWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    userWindow.close();
                    window.close();
                }

                sf::Vector2i mouseP = sf::Mouse::getPosition(userWindow);
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (SaveClicked2.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y)) //if the SAVE button is clicked
                        {
                            saveClicked2U = true;
                            userProfParameter = stringDisplayU; //take the user input as a string that will be the parameter for the link logger class

                            //checking if test was chosen to be ran
                            if ((userProfParameter == "test" || userProfParameter == "Test" || userProfParameter == "TEST" || userProfParameter == "test mode" || userProfParameter == "testing" || userProfParameter == "run tests") && testRan == false)
                            {
                                testRan = true;
                                int result = Catch::Session().run(argc, argv);
                            }
                            //checking if an invalid name has been chose
                            else if ((userProfParameter == "test" || userProfParameter == "Test" || userProfParameter == "TEST" || userProfParameter == "test mode" || userProfParameter == "testing" || userProfParameter == "run tests") && testRan == true)
                            {
                                stringDisplayU.clear();
                                textDisplayU.setString("Invalid Name!");
                                firstClickU = true;
                            }
                            //checking if the user input is all spaces or an empty string, which is invalid
                            else if (userProfParameter.find_first_not_of(' ') == std::string::npos || userProfParameter == "")
                            {
                                stringDisplayU.clear();
                                textDisplayU.setString("Invalid Name!");
                                firstClickU = true;
                            }
                            //closing the user profile window and then opening the main program window and making the link logger class with the correct name parameter
                            else
                            {
                                userBoxOpen = false;
                                userWindow.close();
                                window.create(sf::VideoMode(1480, 1024), "Link Logger");
                                meetingList = new linkLogger(userProfParameter);
                            }
                        }
                        //clearing the box if something other than the SAVE button or textbox was clicked
                        if (!userBox.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y) && !SaveClicked2.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputU = false;
                            stringDisplayU.clear();
                            firstClickU = true;
                            textTracker = 0;
                        }
                        //if the textbox is clicked allow the user to input keys
                        else if (userBox.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputU = true;
                            if (firstClickU)
                            {
                                textDisplayU.setString("");
                                firstClickU = false;
                            }
                        }
                    }
                }
                //taking in user input into the text box and updating it in real time
                if (event.type == sf::Event::TextEntered)
                {
                    //ONLY TAKE INPUT IN IF ALLOWED I.E. WHEN THE SEARCH BAR HAS BEEN SELECTED
                    if (takeInputU == true)
                    {
                        //CHECKING IF THE CHARACTER TYPED IS VALID UNICODE
                        if (event.text.unicode >= 32 && event.text.unicode <= 127)
                        {
                            stringDisplayU += event.text.unicode;
                            textDisplayU.setString(stringDisplayU.substring(textTracker,stringDisplayU.getSize()));
                            //allows for the text to wrap in the textbox so if the string gets larger than the textbox, the first character will not be displayed until it fits in the textbox
                            while (textDisplayU.getLocalBounds().width >= userBox.getSprite().getLocalBounds().width - 60)
                            {
                                textTracker++;
                                string tempString = textDisplayU.getString();
                                tempString = stringDisplayU.substring(textTracker, tempString.size());
                                textDisplayU.setString(tempString);
                            }
                        }
                        //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                        else if (event.text.unicode == 8)
                        {
                            if (!stringDisplayU.isEmpty())
                            {
                                stringDisplayU.erase(stringDisplayU.getSize() - 1, 1);
                                textDisplayU.setString(stringDisplayU);
                            }
                            
                            if(textTracker > 0) //if characters have been wrapped, so text tracker is larger than its default, then we will decrease text tracker so that the string unwraps
                            {
                                textTracker--;
                                string tempString = textDisplayU.getString();
                                tempString = stringDisplayU.substring(textTracker, tempString.size());
                                textDisplayU.setString(tempString);
                            }
                        }
                    }
                }
                //checking if the for keyboard presses
                if (event.type == sf::Event::KeyPressed)
                {
                    //If the enter key is pressed, act as if the save button has been pressed.
                    if (event.key.code == sf::Keyboard::Return)
                    {
                        saveClicked2U = true;
                        userProfParameter = stringDisplayU; //take the user input as a string that will be the parameter for the link logger class

                        //checking if test was chosen to be ran
                        if ((userProfParameter == "test" || userProfParameter == "Test" || userProfParameter == "TEST" || userProfParameter == "test mode" || userProfParameter == "testing" || userProfParameter == "run tests") && testRan == false)
                        {
                            testRan = true;
                            int result = Catch::Session().run(argc, argv);
                        }
                        //checking if an invalid name has been chose
                        else if ((userProfParameter == "test" || userProfParameter == "Test" || userProfParameter == "TEST" || userProfParameter == "test mode" || userProfParameter == "testing" || userProfParameter == "run tests") && testRan == true)
                        {
                            textDisplayU.setString("Invalid Name!");
                            firstClickU = true;
                        }
                        //closing the user profile window and then opening the main program window and making the link logger class with the correct name parameter
                        else
                        {
                            userBoxOpen = false;
                            userWindow.close();
                            window.create(sf::VideoMode(1480, 1024), "Link Logger");
                            meetingList = new linkLogger(userProfParameter);
                        }
                    }
                }
            }
        }
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
                        string tempURL = stringDisplayURL;
                        string tempDesc = stringDisplayD;
                        string tempTime = stringDisplayT;
                        string tempPass = stringDisplayP;
                        string tempDate = "Monday for now fix later!";
                        meetingList->insertMeeting(tempURL, tempDesc, tempTime, tempDate, tempPass);
                        stringDisplayP = "";
                        stringDisplayT = "";
                        stringDisplayD = "";
                        stringDisplayURL = "";
                    }

                    if (CheckClickedAddLink)
                    {
                        //IF IT IS NOT CLICKED
                        if (!LinkAdressInsert.getSprite().getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            takeInputURL = false;
                            textTrackerURL = 0;
                        }                        //IF THE SEARCH BAR IS CLICKED
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
                        {
                            takeInputD = false;
                            textTrackerD = 0;
                        }                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
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
                        {
                            takeInputP = false;
                            textTrackerP = 0;
                        }
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
                        {
                            takeInputT = false;
                            textTrackerT = 0;
                        }                        //IF THE SEARCH BAR IS CLICKED, CLEAR IT AND BEGIN ALLOWING KEYBOARD INPUT TO BE TAKEN IN
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
                        textDisplayURL.setString(stringDisplayURL.substring(textTrackerURL, stringDisplayURL.getSize()));
                        //allows for the text to wrap in the textbox so if the string gets larger than the textbox, the first character will not be displayed until it fits in the textbox
                        while (textDisplayURL.getLocalBounds().width >= LinkAdressInsert.getSprite().getLocalBounds().width - 100)
                        {
                            textTrackerURL++;
                            string tempString = textDisplayURL.getString();
                            tempString = stringDisplayURL.substring(textTrackerURL, tempString.size());
                            textDisplayURL.setString(tempString);
                        }
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayURL.isEmpty())
                        {
                            stringDisplayURL.erase(stringDisplayURL.getSize() - 1, 1);
                            textDisplayURL.setString(stringDisplayURL);
                        }
                        if (textTrackerURL > 0) //if characters have been wrapped, so text tracker is larger than its default, then we will decrease text tracker so that the string unwraps
                        {
                            textTrackerURL--;
                            string tempString = textDisplayURL.getString();
                            tempString = stringDisplayURL.substring(textTrackerURL, tempString.size());
                            textDisplayURL.setString(tempString);
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
                        textDisplayD.setString(stringDisplayD.substring(textTrackerD, stringDisplayD.getSize()));
                        //allows for the text to wrap in the textbox so if the string gets larger than the textbox, the first character will not be displayed until it fits in the textbox
                        while (textDisplayD.getLocalBounds().width >= Description.getSprite().getLocalBounds().width - 100)
                        {
                            textTrackerD++;
                            string tempString = textDisplayD.getString();
                            tempString = stringDisplayD.substring(textTrackerD, tempString.size());
                            textDisplayD.setString(tempString);
                        }
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayD.isEmpty())
                        {
                            stringDisplayD.erase(stringDisplayD.getSize() - 1, 1);
                            textDisplayD.setString(stringDisplayD);
                        }
                        if (textTrackerD > 0) //if characters have been wrapped, so text tracker is larger than its default, then we will decrease text tracker so that the string unwraps
                        {
                            textTrackerD--;
                            string tempString = textDisplayD.getString();
                            tempString = stringDisplayD.substring(textTrackerD, tempString.size());
                            textDisplayD.setString(tempString);
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
                        textDisplayP.setString(stringDisplayP.substring(textTrackerP, stringDisplayP.getSize()));
                        //allows for the text to wrap in the textbox so if the string gets larger than the textbox, the first character will not be displayed until it fits in the textbox
                        while (textDisplayP.getLocalBounds().width >= Password.getSprite().getLocalBounds().width - 100)
                        {
                            textTrackerP++;
                            string tempString = textDisplayP.getString();
                            tempString = stringDisplayP.substring(textTrackerP, tempString.size());
                            textDisplayP.setString(tempString);
                        }
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayP.isEmpty())
                        {
                            stringDisplayP.erase(stringDisplayP.getSize() - 1, 1);
                            textDisplayP.setString(stringDisplayP);
                        }
                        if (textTrackerP > 0) //if characters have been wrapped, so text tracker is larger than its default, then we will decrease text tracker so that the string unwraps
                        {
                            textTrackerP--;
                            string tempString = textDisplayP.getString();
                            tempString = stringDisplayP.substring(textTrackerP, tempString.size());
                            textDisplayP.setString(tempString);
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
                        textDisplayT.setString(stringDisplayT.substring(textTrackerT, stringDisplayT.getSize()));
                        //allows for the text to wrap in the textbox so if the string gets larger than the textbox, the first character will not be displayed until it fits in the textbox
                        while (textDisplayT.getLocalBounds().width >= Time.getSprite().getLocalBounds().width - 100)
                        {
                            textTrackerT++;
                            string tempString = textDisplayT.getString();
                            tempString = stringDisplayT.substring(textTrackerT, tempString.size());
                            textDisplayT.setString(tempString);
                        }
                    }
                    //CHECKING FOR BACKSPACE, WHICH DELETES THE LAST CHARACTER TYPED IF THERE IS A LETTER IN THE SEARCH BAR
                    else if (event.text.unicode == 8)
                    {
                        if (!stringDisplayT.isEmpty())
                        {
                            stringDisplayT.erase(stringDisplayT.getSize() - 1, 1);
                            textDisplayT.setString(stringDisplayT);
                        }
                        if (textTrackerT > 0) //if characters have been wrapped, so text tracker is larger than its default, then we will decrease text tracker so that the string unwraps
                        {
                            textTrackerT--;
                            string tempString = textDisplayT.getString();
                            tempString = stringDisplayT.substring(textTrackerT, tempString.size());
                            textDisplayT.setString(tempString);
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
        if (userBoxOpen)
        {
            userWindow.clear(sf::Color::White);
            userWindow.draw(SaveClicked2.getSprite());
            userWindow.draw(userBox.getSprite());
            if(takeInputU == false)
            {
                textDisplayU.setString("User Profile Name");
            }
            userWindow.draw(textDisplayU);
            userWindow.display();
        }

        window.display();
    }

    return 0;
}
