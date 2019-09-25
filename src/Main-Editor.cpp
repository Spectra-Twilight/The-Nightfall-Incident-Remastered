#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Spybot/EditorGUI.hpp>

using namespace std;
using namespace Spybot;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Nightfall Editor");
    sf::Event event;
    const sf::Color clearColor(0, 16, 57);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch(event.type)
            {   //------------------------------------------------------------------------------------------------------------------------------------------------
                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
            }   //------------------------------------------------------------------------------------------------------------------------------------------------
        }

        window.clear(clearColor);
        // Draw call(s) here.
        window.display();
    }
}