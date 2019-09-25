#include <Spybot/Button.hpp>

#include <cassert>

using namespace std;
using namespace Spybot;

//==============================================================================================================================================================

bool Button::hasMouseCursor(const sf::Event& event)
{
    assert(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased);

    return (event.mouseButton.x >= topLeft.x &&
            event.mouseButton.y >= topLeft.y &&
            event.mouseButton.x < bottomRight.x &&
            event.mouseButton.y < bottomRight.y);
}

//==============================================================================================================================================================

bool Button::onMouseButtonPressed(const sf::Event& event)
{
    assert(!pressed);

    if (hasMouseCursor(event))
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            pressed = true;
        
        return true;
    }
    else
        return false;
}

//==============================================================================================================================================================

bool Button::onMouseButtonReleased(const sf::Event& event)
{
    if (hasMouseCursor(event))
    {
        if (pressed && event.mouseButton.button == sf::Mouse::Button::Left)
        {
            pressed = false;
            clicked = true;
        }

        return true;
    }
    else
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            pressed = false;
        
        return false;
    }
}

//==============================================================================================================================================================

void Button::setPosition(const sf::Vector2f& newPos)
{
    sf::Vector2f size = bottomRight - topLeft;
    topLeft = newPos;
    bottomRight = topLeft + size;
}

//==============================================================================================================================================================