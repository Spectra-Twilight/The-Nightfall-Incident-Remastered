#include <Spybot/Program_Factory_Data/Reader.hpp>

#include <cstdint>

#include <Log.hpp>

using namespace std;
using namespace Spybot;

//============================================================================================================================================================

bool Program::Factory::Data::Reader::get(string& destID, Program::Factory& destData)
{
    if (!has())
        return false;
    
    uint16_t dataElementSize;
    uint8_t temp8bit;
    char tempStr[MaxStringSize]; // Using char[] instead of string prevents unnecessary repeated heap allocations from occuring when reading.

    // Program::Factory data format is defined in Program_Factory_Data/Interface.hpp

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Number of bytes for this data element.
    file.read((char*)(&dataElementSize), DataElementSizeBytes);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // ID
    getline(file, destID, '\0');

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Name
    file.getline(tempStr, MaxStringSize, '\0');
    destData.setName(tempStr);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Description
    file.getline(tempStr, MaxStringSize, '\0');
    destData.setDescription(tempStr);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Move Speed
    file.read((char*)(&temp8bit), MoveSpeedBytes);
    destData.setMoveSpeed(temp8bit);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Max Size
    file.read((char*)(&temp8bit), MaxSizeBytes);
    destData.setMaxSize(temp8bit);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Number of Commands
    file.read((char*)(&temp8bit), NumCommandsBytes);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Command IDs
    for (uint8_t i = 0; i < temp8bit; i++)
    {
        file.getline(tempStr, MaxStringSize, '\0');
        destData.addCommandID(tempStr);
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Graphic ID
    file.getline(tempStr, MaxStringSize, '\0');
    destData.setGfxID(tempStr);

    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    // Color
    {
        uint8_t tempArr[ColorBytes];
        file.read((char*)tempArr, ColorBytes);
        sf::Color tempColor(tempArr[0], tempArr[1], tempArr[2]);
        destData.setColor(tempColor);
    }

    // Reset to beginning of element.
    file.seekg(-dataElementSize, ios_base::cur);
    return true;
}

//============================================================================================================================================================