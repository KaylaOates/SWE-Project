#define CATCH_CONFIG_RUNNER
#include "Notification.h"
#include "catch2/catch.hpp"
#include "TextBox.cpp"
#include "LinkLogger.h"
#include <set>
#include "functions.h"
#include <SFML/Graphics.hpp>
#include <stdlib.h> 
#include <random>
#include <chrono>


int main(int argc, char* const argv[])
{

	//declare all window, shape, text, font objects here
    sf::RenderWindow window;
    sf::RenderWindow userWindow(sf::VideoMode(600, 480), "Select User Profile");
    bool userBoxOpen = true;   
    sf::RenderWindow notificationWindow;
    vector<sf::CircleShape*> removeButtons;
    bool notiBoxOpen = false;
    linkLogger tempLinkLogger = linkLogger();
    linkLogger* meetingList = &tempLinkLogger;
    random_device dev;
    mt19937::result_type seed = dev() ^(
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count() +
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count());
    mt19937 rng(seed);
    uniform_int_distribution<mt19937::result_type> color1(100, 235);
    uniform_int_distribution<mt19937::result_type> color3(0, 150);


    int colorStart = color3(rng);
    vector<int> colors;
    for (int k = 0; k < 1000; k++)
    {
        colors.push_back(color1(rng));
    }
    set<meeting*> notifications; //USE THIS TO TURN ON AND OFF THE ALARM;
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
    textDisplayURL.setString("Insert URL (Include www.)");
    bool firstClickURL = true;
    int textTrackerURL = 0;

    int removeBTracker = 0;

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
    textDisplayT.setString("Time(Ex:\"5:00 PM monday\")");
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

    sf::Text textDisplayNoti;
    textDisplayNoti.setFont(font);
    textDisplayNoti.setCharacterSize(25);
    textDisplayNoti.setStyle(sf::Text::Bold);
    textDisplayNoti.setStyle(sf::Text::Underlined);
    textDisplayNoti.setFillColor(sf::Color::Red);
    textDisplayNoti.setOutlineThickness(2);

    sf::CircleShape downButton(30,3);
    downButton.rotate(180);
    downButton.setFillColor(sf::Color::Color(73, 73, 73));;
    downButton.setPosition(1355, 875);
    downButton.setOutlineColor(sf::Color::Color(231, 231, 231));
    downButton.setOutlineThickness(3);
    sf::CircleShape upButton(30, 3);
    upButton.setFillColor(sf::Color::Color(73, 73, 73));
    upButton.setPosition(1300, 350);
    upButton.setOutlineColor(sf::Color::Color(231, 231, 231));
    upButton.setOutlineThickness(3);
    


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
    ImportImage ListViewBackground("ListViewBackground", 105, 280);
    ImportImage ClickedListView("ClickedListView", 50, 30);
    bool CheckClickedListView = false;
    ImportImage LinkAdressInsert("LinkAdressInsert", 220, 300);
    ImportImage Description("Description", 220, 450);
    ImportImage Password("Password", 220, 600);
    ImportImage Time("Time", 220, 750);
    ImportImage SaveUnclicked("SaveUnclicked", 600, 885);
    ImportImage SaveClicked("SaveClicked", 600, 885);
    bool CheckSaveClicked = false;
        
    ImportImage calendarViewBG("calendarViewBackground", 0, 200);
    ImportImage userBox("UsersB", 40, 100);
    ImportImage SaveClicked2("SaveUnclicked", 170, 250);
    string userProfParameter;
    bool saveClicked2U = false;
    
    
    /////////////////////////////////////////////////////////////FOR TESTING NOTIFICATION WINDOW PURPOSES ONLY DELETE WHEN DONE!///////////////////////////////////////////////////////////
    bool notiWindow = true;

    //---------------------------------------------------------------MAIN PROGRAM LOOP-------------------------------------------------------------------//
    bool testRan = false;
    int textTracker = 0;
    notiWindow = true;

    while (window.isOpen() || userWindow.isOpen() || notificationWindow.isOpen())
    {
        meeting* alertMeeting = meetingList->checkMeetingAlerts();
        if (alertMeeting != nullptr)
        {
            notifications.insert(alertMeeting); //SO I WANT TO USE WHAT IS IN THE SET, IF THERE IS SOMETHING, HAVE THE ALARM GO OFF UNTIL THE USER CLICKS THE TURN OFF BUTTON. THEN WHEN THE TURN OFF BUTTON IS PRESSED, USE DISALLOWNOISE(), WAIT 5 MINUTES AND USE ALLOWNOISE()
        }
        if (notifications.size() > 0 && !userBoxOpen)
        {
            auto it = notifications.begin();
            meeting* tempMeetingPtr = *it;
            notiBoxOpen = true;
            textDisplayNoti.setString(tempMeetingPtr->getInfo());
            auto boxSize = textDisplayNoti.getGlobalBounds();
            int boxWidth = 250 - ((boxSize.width) / 2);
            textDisplayNoti.setPosition(boxWidth, 25);
            if (notiWindow)
            {
                notificationWindow.create(sf::VideoMode(500, 100), "Meeting Time!");
                notiWindow = false;
            }
        }

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
        if (notiBoxOpen)
        {
            while (notificationWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    notificationWindow.close();
                    notiBoxOpen = false;
                    if (notifications.size() > 0 && !userBoxOpen)
                    {
                        
                        auto it = notifications.begin();
                        meeting* tempMeetingPtr = *it;
                        tempMeetingPtr->allow_Noise();
                        notifications.clear();
                    }
                }
                sf::Vector2i mouseP = sf::Mouse::getPosition(notificationWindow);
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (textDisplayNoti.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            auto it = notifications.begin();
                            meeting* tempMeetingPtr = *it;
                            meetingList->openURL(tempMeetingPtr->getURL());
                            tempMeetingPtr->disallowNoise();
                            notiBoxOpen = false;
                            OpenClipboard(0);
                            EmptyClipboard();
                            auto data = GlobalAlloc(GMEM_FIXED, 32);
                            string tempString = tempMeetingPtr->getPassword();
                            const char* tempC = tempString.c_str();
                            memcpy(data, tempC, tempString.size()+1);
                            SetClipboardData(CF_TEXT, data);
                            CloseClipboard();
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
                    if (CheckClickedListView)
                    {
                        int x = 5;
                        if (removeButtons.size() < 5)
                        {
                            x = removeButtons.size();
                        }
                        for (int i = 0; i < x; i++)
                        {
                            if (removeButtons[i]->getGlobalBounds().contains(mouseP.x, mouseP.y))
                            {
                                meetingList->removeLink(meetingList->getMeetingInt(i+removeBTracker));
                            }
                        }
                        if (downButton.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            removeBTracker++;
                            if (removeBTracker + 5 > meetingList->getCount())
                                removeBTracker--;
                        }
                        if (upButton.getGlobalBounds().contains(mouseP.x, mouseP.y))
                        {
                            removeBTracker--;
                            if (removeBTracker < 0)
                                removeBTracker = 0;
                        }
                    }


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
                        meetingList->insertMeeting(tempURL, tempDesc, tempTime, tempPass);
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
         {
            for (int i = 0; i < removeButtons.size(); i++)
            {
                delete removeButtons[i];
            }
            window.draw(ClickedListView.getSprite());
            window.draw(ListViewBackground.getSprite());

            int numLinks = meetingList->getCount();
            removeButtons.resize(numLinks);
            int lastLink = removeBTracker + 5;
            if (numLinks-removeBTracker < 5)
            {
                lastLink = numLinks;
            }


            window.draw(downButton);
            window.draw(upButton);
            int i = 0;
            int j = 0;
            if (numLinks > 4)
            {
                j = removeBTracker;
            }
            for (; j < lastLink; j++)
            {
                sf::Texture Textures;
                sf::Sprite Sprites;
                sf::CircleShape* removeButton = new sf::CircleShape();
                
                int y = 325 + (i*115);


                removeButton->setPosition(270, y + 32);
                removeButton->setFillColor(sf::Color::Red);
                removeButton->setRadius(17);
                removeButtons[i] = removeButton;

                Textures.loadFromFile("Images/ListViewDisplay.png");
                Sprites.setTexture(Textures);
                Sprites.setPosition(sf::Vector2f(250, y));
                window.draw(Sprites);

                sf::Text Link;
                Link.setFont(font);
                Link.setCharacterSize(30);
                Link.setFillColor(sf::Color::Black);
                Link.setPosition(320, y+30);
                Link.setString(meetingList->getMeetingInt(j)->getInfo());  /// INSERT LINK HERE TO BE DISPLAYED
                window.draw(Link);

                sf::Text Date;
                Date.setFont(font);
                Date.setCharacterSize(30);
                Date.setFillColor(sf::Color::Black);
                Date.setPosition(1090, y + 30);
                Date.setString(meetingList->getMeetingInt(j)->getDate());  /// INSERT NAME HERE TO BE DISPLAYED
                window.draw(Date);

                sf::Text Password;
                Password.setFont(font);
                Password.setCharacterSize(30);
                Password.setFillColor(sf::Color::Black);
                Password.setPosition(700, y + 30);
                string passwordString = "No Password";
                if (meetingList->getMeetingInt(i)->getPassword() != "")
                    passwordString = meetingList->getMeetingInt(j)->getPassword();
                Password.setString(passwordString);  /// INSERT PASSWORD HERE TO BE DISPLAYED
                window.draw(Password);

                sf::Text Time;
                Time.setFont(font);
                Time.setCharacterSize(30);
                Time.setFillColor(sf::Color::Black);
                Time.setPosition(950, y + 30);
                Time.setString(meetingList->getMeetingInt(j)->getTime());  /// INSERT TIME HERE TO BE DISPLAYED
                window.draw(Time);


                window.draw(*removeButton);
                i++;
            }
        }

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

                textDisplayURL.setString("Insert URL (Include www.)");
                textDisplayP.setString("Password?");
                textDisplayT.setString("Time(Ex:\"5:00 PM monday\")");
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
        {
            window.draw(ClickedCalendarView.getSprite());
            window.draw(calendarViewBG.getSprite());
            int j = 0;
            float horiDiff = 193.2;
            float vertDiff = 45.55;
            for (int i = 0; i < meetingList->getCount(); i++)
            {
                int charSize = 50;
                if (meetingList->getMeetingInt(i)->getDate() == "sunday" || meetingList->getMeetingInt(i)->getDate() == "Sunday" || meetingList->getMeetingInt(i)->getDate() == "SUNDAY")
                    j = 0;
                else if (meetingList->getMeetingInt(i)->getDate() == "monday" || meetingList->getMeetingInt(i)->getDate() == "Monday" || meetingList->getMeetingInt(i)->getDate() == "MONDAY")
                    j = 1;
                else if (meetingList->getMeetingInt(i)->getDate() == "tuesday" || meetingList->getMeetingInt(i)->getDate() == "Tuesday" || meetingList->getMeetingInt(i)->getDate() == "TUESDAY")
                    j = 2;
                else if (meetingList->getMeetingInt(i)->getDate() == "wednesday" || meetingList->getMeetingInt(i)->getDate() == "Wednesday" || meetingList->getMeetingInt(i)->getDate() == "WEDNESDAY")
                    j = 3;
                else if (meetingList->getMeetingInt(i)->getDate() == "thursday" || meetingList->getMeetingInt(i)->getDate() == "Thursday" || meetingList->getMeetingInt(i)->getDate() == "THURSDAY")
                    j = 4;
                else if (meetingList->getMeetingInt(i)->getDate() == "friday" || meetingList->getMeetingInt(i)->getDate() == "Friday" || meetingList->getMeetingInt(i)->getDate() == "FRIDAY")
                    j = 5;
                else if (meetingList->getMeetingInt(i)->getDate() == "saturday" || meetingList->getMeetingInt(i)->getDate() == "Saturday" || meetingList->getMeetingInt(i)->getDate() == "SATURDAY")
                    j = 6;
                else
                    j = 10;
                float tempF = meetingList->getMeetingInt(i)->getMTime();
                tempF = tempF - 6;
                if (tempF < 0 || tempF > 16)
                    continue;

                sf::RectangleShape linkBox;
                linkBox.setSize(sf::Vector2f(195, 45));
                linkBox.setFillColor(sf::Color::Color(colors[colorStart +(1*(i+1))], colors[colorStart +(2 * (i + 1))], colors[colorStart +(3 * (i + 1))]));
                linkBox.setPosition(114 + j*horiDiff, 241 + tempF*vertDiff);

                sf::Text Link;
                Link.setFont(font);
                Link.setCharacterSize(charSize);
                Link.setFillColor(sf::Color::Black);
                string tempStringInfo = meetingList->getMeetingInt(i)->getInfo();
                Link.setString(tempStringInfo);  /// INSERT LINK HERE TO BE DISPLAYED
                auto boxSize = Link.getGlobalBounds();
                int boxWidth = 210 - ((boxSize.width) / 2);
                int boxHeight = 255 - ((boxSize.height) / 2);
                Link.setPosition(boxWidth + j * horiDiff, boxHeight + tempF * vertDiff);

                while (Link.getLocalBounds().width >= linkBox.getLocalBounds().width || Link.getLocalBounds().height > linkBox.getLocalBounds().height)
                {
                    charSize--;
                    Link.setCharacterSize(charSize);
                    auto boxSize = Link.getGlobalBounds();
                    int boxWidth = 210 - ((boxSize.width) / 2);
                    int boxHeight = 255 - ((boxSize.height) / 2);
                    Link.setPosition(boxWidth + j * horiDiff, boxHeight + tempF * vertDiff);
                }
                window.draw(linkBox);
                window.draw(Link);
            }
        }
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
        if (notiBoxOpen && !userBoxOpen)
        {
            notificationWindow.clear(sf::Color::White);
            notificationWindow.draw(textDisplayNoti);
            notificationWindow.display();

        }

        window.display();
    }

    return 0;
}
