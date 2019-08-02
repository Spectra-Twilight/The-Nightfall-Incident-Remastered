#include <Spybot/Program_Factory.hpp>

#include <sstream>

using namespace std;
using namespace Spybot;

const string Program::Factory::error_name = "Name not found.";
const string Program::Factory::error_description = "Description not found.";
const string Program::Factory::error_icon = "data/gfx/icons/error.png";
const sf::Color Program::Factory::error_color = sf::Color::White;

void Program::Factory::define(const DataLoader& loader)
{
    string tempStr;
    int tempInt;

    // Load name
    name = loader.getAttributeValue("name");
    if (name.length() == 0)
        name = error_name;

    // Load description
    description = loader.getAttributeValue("desc");
    if (description.length() == 0)
        description = error_description;

    // Load maxSize
    tempStr = loader.getAttributeValue("size");
    if (tempStr.length() > 0 && (tempInt = stoi(tempStr)))
        maxSize = tempInt;
    else
        maxSize = error_maxSize;

    // Load moveSpeed
    tempStr = loader.getAttributeValue("move");
    if (tempStr.length() > 0 && (tempInt = stoi(tempStr)) <= 255)
        moveSpeed = tempInt;
    else
        moveSpeed = error_moveSpeed;

    // Load and parse commands
    tempStr = loader.getAttributeValue("commands");
    if (tempStr.length() > 0)
    {
        stringstream stream(tempStr);

        while (stream.good())
        {
            stream >> tempStr;
            if (tempStr.length() > 0)
                commandIDs.push_back(tempStr);
        }
    }

    // Load icon
    if (!icon.loadFromFile(loader.getAttributeValue("icon")))
        icon.loadFromFile(error_icon);

    // Load color
    tempStr = loader.getAttributeValue("color");
    if (tempStr.length() > 0)
    {
        stringstream stream(tempStr);

        uint8_t rgb[3];
        for (uint8_t i = 0; stream.good() && i < 3; i++)
        {
            stream >> tempStr;
            if (tempStr.length() > 0 && (tempInt = stoi(tempStr)) <= 255)
                rgb[i] = tempInt;
            else
                rgb[i] = 0;
        }
        color = sf::Color(rgb[0], rgb[1], rgb[2]);
    }
    else
        color = error_color;
}