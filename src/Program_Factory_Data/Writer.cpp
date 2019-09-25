#include <Spybot/Program_Factory_Data/Writer.hpp>

#include <cstdint>
#include <list>

#include <Log.hpp>

using namespace std;
using namespace Spybot;

//========================================================================================================================================================

bool Program::Factory::Data::Writer::put(const string& srcID, const Program::Factory& srcData)
{
    if (!file.is_open())
        return false;
    
    constexpr uint16_t InitialDataElementSize = DataElementSizeBytes + MoveSpeedBytes + MaxSizeBytes + NumCommandsBytes + ColorBytes;
    uint16_t dataElementSize = InitialDataElementSize;
    uint8_t temp8bit;

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Data element size

    // Accumulate total size.
    dataElementSize += srcID.size();
    dataElementSize += srcData.getName().size();
    dataElementSize += srcData.getDescription().size();
    for (list<string>::const_iterator iter = srcData.getCommandIDs().begin(); iter != srcData.getCommandIDs().end(); iter++)
        dataElementSize += iter->size();
    dataElementSize += srcData.getGfxID().size();

    // Write
    file.write((char*)(&dataElementSize), DataElementSizeBytes);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // ID
    file.write(srcID.c_str(), srcID.size() + 1);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Name
    file.write(srcData.getName().c_str(), srcData.getName().size() + 1);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Description
    file.write(srcData.getDescription().c_str(), srcData.getDescription().size() + 1);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Move Speed
    temp8bit = srcData.getMoveSpeed();
    file.write((char*)(&temp8bit), MoveSpeedBytes);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Max Size
    temp8bit = srcData.getMaxSize();
    file.write((char*)(&temp8bit), MaxSizeBytes);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Number of commands
    temp8bit = srcData.getCommandIDs().size();
    file.write((char*)(&temp8bit), NumCommandsBytes);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Command IDs
    for (list<string>::const_iterator iter = srcData.getCommandIDs().begin(); iter != srcData.getCommandIDs().end(); iter++)
        file.write(iter->c_str(), iter->size() + 1);
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Graphic ID
    file.write(srcData.getGfxID().c_str(), srcData.getGfxID().size() + 1);

    //----------------------------------------------------------------------------------------------------------------------------------------------------
    // Color
    {
        const sf::Color& color = srcData.getColor();
        uint8_t tempArr[ColorBytes] = {color.r, color.g, color.b};
        file.write((char*)tempArr, ColorBytes);
    }

    numDataElements++;
    return true;
}

//========================================================================================================================================================