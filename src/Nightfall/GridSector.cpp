#include <Nightfall/GridSector.hpp>

#include <stdexcept>

#include <Log.hpp>

using namespace std;
using namespace nf;

//==================================================================================================================================================

const string GridSector::defaultGfxDir = "data/gfx/sectors/default.png";
sf::Texture GridSector::defaultGfx;
const sf::Color GridSector::color = sf::Color(255, 255, 255, 64);
unsigned int GridSector::sideLength = baseSideLength;

//==================================================================================================================================================

GridSector::GridSector(const sf::Texture& sectorTexture, bool isActive): active(isActive), linkRight(false), linkDown(false), program(nullptr)
{
    sectorGfx.setTexture(sectorTexture);
    sectorGfx.setColor(color);

    const sf::Texture& programTexture = Program::getBaseGfx();
    programGfx.setTexture(programTexture);
    linkRightGfx.setTexture(programTexture);
    linkDownGfx.setTexture(programTexture);

    linkRightGfx.setScale(linkScale, linkScale);
    linkDownGfx.setScale(linkScale, linkScale);
}

//==================================================================================================================================================

void GridSector::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (active)
    {
        if (program)
        {
            target.draw(programGfx);

            if (linkRight)
                target.draw(linkRightGfx);
            if (linkDown)
                target.draw(linkDownGfx);
        }
        else
            target.draw(sectorGfx);
    }
}

//==================================================================================================================================================

bool GridSector::notifyMouseMovedEvent(sf::Event event)
{
    sf::Vector2f topLeft = sectorGfx.getPosition();
    sf::Vector2f bottomRight = topLeft;
    bottomRight.x += sideLength;
    bottomRight.y += sideLength;

    return (event.mouseMove.x >= topLeft.x &&
            event.mouseMove.x < bottomRight.x && 
            event.mouseMove.y >= topLeft.y && 
            event.mouseMove.y < bottomRight.y);
}

//==================================================================================================================================================

void GridSector::setPosition(const sf::Vector2f& pos)
{
    sectorGfx.setPosition(pos);
    programGfx.setPosition(pos);

    sf::Vector2u gfxSize = programGfx.getTexture()->getSize();
    sf::Vector2f linkPos = pos;

    // Establish position of right link.
    linkPos.x += gfxSize.x - Program::baseGfxEdge;
    linkPos.y += gfxSize.y * linkScale;
    linkRightGfx.setPosition(linkPos);

    linkPos = pos;
    // Establish position of down link.
    linkPos.y += gfxSize.y - Program::baseGfxEdge;
    linkPos.x += gfxSize.x * linkScale;
    linkDownGfx.setPosition(linkPos);
}

//==================================================================================================================================================

void GridSector::setProgram(const Program* newProgram)
{
    program = newProgram;

    const sf::Color& newColor = program->getColor();
    programGfx.setColor(newColor);
    linkRightGfx.setColor(newColor);
    linkDownGfx.setColor(newColor);
}

//==================================================================================================================================================