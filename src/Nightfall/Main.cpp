////////////////////////////////////////////////////////////////////////////////
/// Standard Library Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// Nightfall Includes
////////////////////////////////////////////////////////////////////////////////
#include <Nightfall/Program.hpp>
#include <Nightfall/Sector.hpp>

////////////////////////////////////////////////////////////////////////////////
/// SFML Includes
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////////////////////////
/// Miscellaneous Includes
////////////////////////////////////////////////////////////////////////////////
#include <Log.hpp>
#include <Trie/trie.hpp>

int main()
{
    Log::open_ts("log/", "nightfall", Log::Level::debug);
    // nightfall::Program::loadBaseGfx();
    // nightfall::Sector::loadDefaultSectorGfx();

    //Game game;
    sf::Font testFont;
    testFont.loadFromFile("data/font/Spybot-bold-8.bdf");
    sf::Text testText("SHOW PROGRAMS", testFont, 8);
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "The Nightfall Incident: Remastered", sf::Style::Titlebar | sf::Style::Close);
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

    Log::close();
    return 0;
}