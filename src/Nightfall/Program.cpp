#include <Nightfall/Program.hpp>
#include <Nightfall/Program_Factory.hpp>

using namespace std;
using namespace nightfall;

//======================================================================================================================================================

const string Program::BaseGfxDir = "data/gfx/programs/base.png";
sf::Texture Program::baseGfx;

//======================================================================================================================================================

Program::Program(const Factory* baseProgram): factory(baseProgram)
{
    maxSize = factory->getMaxSize();
    speed = factory->getMoveSpeed();

//  TODO
//    icon.setTexture(factory->getIcon());
}

//======================================================================================================================================================

void Program::addNewestSector(GridSector* newSector)
{
    list<GridSector*>::iterator sectorIter;
    bool foundMatch = false;
    for (sectorIter = sectors.begin(); sectorIter != sectors.end() && !foundMatch; sectorIter++)
    {
        if (*sectorIter == newSector)
        {
            sectors.erase(sectorIter);
            foundMatch = true;
        }
    }

    sectors.push_front(newSector);
}

//======================================================================================================================================================

void Program::addOldestSector(GridSector* oldSector)
{
    list<GridSector*>::iterator sectorIter;
    bool foundMatch = false;
    for (sectorIter = sectors.begin(); sectorIter != sectors.end() && !foundMatch; sectorIter++)
    {
        if (*sectorIter == oldSector)
        {
            sectors.erase(sectorIter);
            foundMatch = true;
        }
    }

    sectors.push_back(oldSector);
}

//======================================================================================================================================================

const sf::Color& Program::getColor() const
{
    return factory->getColor();
}

//======================================================================================================================================================

const list<Command*>& Program::getCommands() const
{
    return factory->getCommands();
}

//======================================================================================================================================================

const string& Program::getDescription() const
{
    return factory->getDescription();
}

//======================================================================================================================================================

const string& Program::getName() const
{
    return factory->getName();
}

//======================================================================================================================================================

GridSector* Program::getNewestSector() const
{
    if (sectors.empty())
        return nullptr;

    return sectors.front();
}

//======================================================================================================================================================

GridSector* Program::getOldestSector() const
{
    if (sectors.empty())
        return nullptr;

    return sectors.back();
}

//======================================================================================================================================================

GridSector* Program::removeNewestSector()
{
    if (sectors.empty())
        return nullptr;
    
    GridSector* sector = sectors.front();
    sectors.pop_front();
    return sector;
}

//======================================================================================================================================================

GridSector* Program::removeOldestSector()
{
    if (sectors.empty())
        return nullptr;
    
    GridSector* sector = sectors.back();
    sectors.pop_back();
    return sector;
}

//======================================================================================================================================================