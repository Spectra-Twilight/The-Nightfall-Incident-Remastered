#include <Log.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    Log::openLog("log/", Log::Level::DEBUG);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Spybot: The Nightfall Incident", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Draw stuff here.
        window.display();
    }

    Log::closeLog();
    return 0;
}