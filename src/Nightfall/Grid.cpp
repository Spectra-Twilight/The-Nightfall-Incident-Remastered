#include <Nightfall/Grid.hpp>

using namespace std;
using namespace nf;

//======================================================================================================================================================

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    uint8_t y, x;
    for (y = 0; y < SectorHeight; y++)
    {
        for (x = 0; x < SectorWidth; x++)
        {
            target.draw(sectors[y][x]);
        }
    }
}

//======================================================================================================================================================

bool Grid::onMouseButtonPressed(const sf::Event& event)
{
    // First: Determine if the mouse was inside of the Grid when pressed.
    sf::Vector2f topLeft = sectors[0][0].getPosition();
    sf::Vector2f bottomRight = sectors[SectorHeight - 1][SectorWidth - 1].getPosition();
    bottomRight.x += GridSector::getSideLength();
    bottomRight.y += GridSector::getSideLength();
    
    if (event.mouseButton.x >= topLeft.x &&
        event.mouseButton.x < bottomRight.x && 
        event.mouseButton.y >= topLeft.y && 
        event.mouseButton.y < bottomRight.y)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left) // Only react to left clicks.
        {
            // Second: Determine if the mouse was inside of a GridSector when pressed, and, if so, which one.
            uint8_t y, x;
            y = x = 0;
            bool stop = false;
            while (!stop && y < SectorHeight)
            {
                float top = sectors[y][0].getPosition().y;
                float bottom = top + GridSector::getSideLength();

                if (event.mouseButton.y >= top && event.mouseButton.y < bottom)
                    stop = true;
                else
                    y++;
            }

            stop = (y >= SectorHeight); // Perform no more searches if outside the bounds of y.
            while (!stop && x < SectorWidth)
            {
                float left = sectors[0][x].getPosition().x;
                float right = left + GridSector::getSideLength();

                if (event.mouseButton.x >= left && event.mouseButton.x < right)
                    stop = true;
                else
                    x++;
            }

            if (y < SectorHeight && x < SectorWidth)
                pressedSector = &sectors[y][x];
        }

        return true; // Mouse was pressed inside of the Grid.
    }
    else
        return false; // Mouse was pressed outside of the Grid.
}

//======================================================================================================================================================

bool Grid::onMouseButtonReleased(const sf::Event& event)
{
    // First: Determine if the mouse was inside of the Grid when released.
    sf::Vector2f topLeft = sectors[0][0].getPosition();
    sf::Vector2f bottomRight = sectors[SectorHeight - 1][SectorWidth - 1].getPosition();
    bottomRight.x += GridSector::getSideLength();
    bottomRight.y += GridSector::getSideLength();
    
    if (event.mouseButton.x >= topLeft.x &&
        event.mouseButton.x < bottomRight.x && 
        event.mouseButton.y >= topLeft.y && 
        event.mouseButton.y < bottomRight.y)
    {
        // Second: Determine if the previously left-mouse-button-pressed sector is now being left-mouse-released.
        if (pressedSector && event.mouseButton.button == sf::Mouse::Button::Left) // Only react to left clicks.
        {
            topLeft = pressedSector->getPosition();
            bottomRight.x = topLeft.x + GridSector::getSideLength();
            bottomRight.y = topLeft.y + GridSector::getSideLength();

            if (event.mouseButton.x >= topLeft.x &&
                event.mouseButton.x < bottomRight.x && 
                event.mouseButton.y >= topLeft.y && 
                event.mouseButton.y < bottomRight.y)
            {
                pressedSector->setActive(false);
            }

            pressedSector = nullptr;
        }

        return true; // Mouse was released inside of the Grid.
    }
    else
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
            pressedSector = nullptr;
        return false; // Mouse was released outside of the Grid.
    }
}

//======================================================================================================================================================

// bool Grid::notifyMouseMovedEvent(sf::Event event)
// {
//     if (mousedSector)
//     {
//         mousedSector->setActive(false);
//         mousedSector = nullptr;
//     }

//     sf::Vector2f topLeft = sectors[0][0].getPosition();
//     sf::Vector2f bottomRight = sectors[SectorHeight - 1][SectorWidth - 1].getPosition();
//     bottomRight.x += GridSector::Width;
//     bottomRight.y += GridSector::Height;

//     if (event.mouseMove.x >= topLeft.x && 
//         event.mouseMove.x < bottomRight.x && 
//         event.mouseMove.y >= topLeft.y && 
//         event.mouseMove.y < bottomRight.y)
//     {
//         bool stop = false;
//         uint8_t y, x;
//         y = x = 0;
//         while (!stop && y < SectorHeight)
//         {
//             float top = sectors[y][0].getPosition().y;
//             float bottom = top + GridSector::Height;
//             if (event.mouseMove.y >= top && event.mouseMove.y < bottom)
//                 stop = true;
//             else
//                 y++;
//         }

//         stop = !(y < SectorHeight);

//         while (!stop && x < SectorWidth)
//         {
//             float left = sectors[y][x].getPosition().x;
//             float right = left + GridSector::Width;
//             if (event.mouseMove.x >= left && event.mouseMove.x < right)
//                 stop = true;
//             else
//                 x++;
//         }

//         if (y < SectorHeight && x < SectorWidth)
//         {
//             mousedSector = &sectors[y][x];
//             mousedSector->setActive(true);
//         }

//         return true;
//     }
//     else
//         return false;
// }

//======================================================================================================================================================

void Grid::setPosition(sf::Vector2f newPos)
{
    sf::Vector2f pos;
    uint8_t y, x;
    for (y = 0; y < SectorHeight; y++)
    {
        pos.x = newPos.x;
        pos.y = newPos.y + (y * (GridSector::getSideLength() + SectorGap));
        for (x = 0; x < SectorWidth; x++)
        {
            sectors[y][x].setPosition(pos);
            pos.x += (GridSector::getSideLength() + SectorGap);
        }
    }
}

//======================================================================================================================================================