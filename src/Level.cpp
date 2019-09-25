#include <Spybot/Level.hpp>

using namespace std;
using namespace Spybot;

//============================================================================================================================================================

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(grid);
}

//============================================================================================================================================================

void Level::onMouseButtonPressed(const sf::Event& event)
{
    if (grid.onMouseButtonPressed(event))
        return;
}

//============================================================================================================================================================

void Level::onMouseButtonReleased(const sf::Event& event)
{
    if (grid.onMouseButtonReleased(event))
        return;
}

//============================================================================================================================================================