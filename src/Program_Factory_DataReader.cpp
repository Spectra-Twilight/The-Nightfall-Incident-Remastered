#include <Spybot/Data/Program_Factory_DataReader.hpp>

#include <cstdint>

using namespace std;
using namespace Spybot;

//==================================================================================================================================================

bool Program::Factory::DataReader::get(std::string& destID, Factory& destData)
{
    if (!file.is_open() || file.peek() == EOF)
        return false;

    // The format for Program::Factory data is defined in Program::Factory::DataInterface.hpp.
    char tempStr[256];
    uint8_t temp8bit;

    uint16_t dataElementSize;
    file.read((char*)(&dataElementSize), DataElementSizeBytes);

    // ID
    file.read((char*)(&temp8bit), IDCharCountBytes);
    file.read(tempStr, temp8bit);
    tempStr[temp8bit] = '\0';
    destID = tempStr;

    // Name
    file.read((char*)(&temp8bit), NameCharCountBytes);
    file.read(tempStr, temp8bit);
    tempStr[temp8bit] = '\0';
    destData.setName(tempStr);

    // Description
    file.read((char*)(&temp8bit), DescCharCountBytes);
    file.read(tempStr, temp8bit);
    tempStr[temp8bit] = '\0';
    destData.setDescription(tempStr);

    // Move Speed
    file.read((char*)(&temp8bit), MoveSpeedBytes);
    destData.setMoveSpeed(temp8bit);

    // Max Size
    file.read((char*)(&temp8bit), MaxSizeBytes);
    destData.setMaxSize(temp8bit);

    // Commands
    file.read((char*)(&temp8bit), NumCommandsBytes);
    {
        uint8_t commandIDChars;
        for (uint8_t c = 0; c < temp8bit; c++)
        {
            file.read((char*)(&commandIDChars), IDCharCountBytes);
            file.read(tempStr, commandIDChars);
            tempStr[commandIDChars] = '\0';
            destData.addCommandID(tempStr);
        }
    }

    // Icon filepath.
    file.read((char*)(&temp8bit), IconFilepathCharCountBytes);
    file.read(tempStr, temp8bit);
    tempStr[temp8bit] = '\0';
    destData.setIconFilepath(tempStr);

    // Color.
    {
        uint8_t colorArray[ColorBytes];
        file.read((char*)colorArray, ColorBytes);
        sf::Color color(colorArray[0], colorArray[1], colorArray[2]);
        destData.setColor(color);
    }

    // Return to the start of this data element.
    file.seekg(-dataElementSize, ios_base::cur);
    return true;
}

//==================================================================================================================================================