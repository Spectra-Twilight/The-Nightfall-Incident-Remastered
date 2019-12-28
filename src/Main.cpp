#include <string>

#include <Log.hpp>
#include <Trie/trie.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Nightfall/Game.hpp>

using namespace std;
using namespace nf;

int main()
{
    Log::openLog("log/", Log::Level::DEBUG);
    Program::loadBaseGfx();
    GridSector::loadDefaultSectorGfx();

    //Game game;
    sf::Font testFont;
    testFont.loadFromFile("data/font/Spybot-bold-8.bdf");
    sf::Text testText("SHOW PROGRAMS", testFont, 8);
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Spybot: The Nightfall Incident", sf::Style::Titlebar | sf::Style::Close);
    // window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {   //-------------------------------------------------------------------------------------------------------------------------------------------------
                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
                //-------------------------------------------------------------------------------------------------------------------------------------------------
                case sf::Event::MouseButtonPressed:
                {
                    // game.onMouseButtonPressed(event);
                }
                break;
                //-------------------------------------------------------------------------------------------------------------------------------------------------
                case sf::Event::MouseButtonReleased:
                {
                    // game.onMouseButtonReleased(event);
                }
                break;
            }   //-------------------------------------------------------------------------------------------------------------------------------------------------
        }

        window.clear(sf::Color::Black);
        // window.draw(game);
        window.draw(testText);
        window.display();
    }

    Log::closeLog();
    return 0;
}