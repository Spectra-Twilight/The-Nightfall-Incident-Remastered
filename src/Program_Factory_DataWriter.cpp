#include <Spybot/Data/Program_Factory_DataWriter.hpp>

using namespace std;
using namespace Spybot;

//==================================================================================================================================================

bool Program::Factory::DataWriter::put(const std::string& srcID, const Factory& srcData)
{
    if (!file.is_open())
        return false;

    // The format for Program::Factory data is defined in Program::Factory::DataInterface.hpp.
    constexpr uint16_t DataElementSizeBeforeStrings = DataElementSizeBytes + IDCharCountBytes + NameCharCountBytes + 
                                                      DescCharCountBytes + MoveSpeedBytes + MaxSizeBytes + NumCommandsBytes +
                                                      IconFilepathCharCountBytes + ColorBytes;

    const list<string>& commandIDs = srcData.getCommandIDs();
    list<string>::const_iterator commandIter;
    uint8_t temp8bit;

    // Determine the size of this data element before writing.
    uint16_t dataElementSize = DataElementSizeBeforeStrings;
    dataElementSize += srcID.size();
    dataElementSize += srcData.getName().size();
    dataElementSize += srcData.getDescription().size();
    dataElementSize += (commandIDs.size() * IDCharCountBytes);
    dataElementSize += srcData.getIconFilepath().size();

    if (commandIDs.size() > 0)
    {
        for (commandIter = commandIDs.begin(); commandIter != commandIDs.end(); commandIter++)
            dataElementSize += commandIter->size();
    }

    // Write the size of this data element.
    file.write((char*)(&dataElementSize), DataElementSizeBytes);

    // ID
    temp8bit = srcID.size();
    file.write((char*)(&temp8bit), IDCharCountBytes);
    file.write(srcID.c_str(), temp8bit);

    // Name
    temp8bit = srcData.getName().size();
    file.write((char*)(&temp8bit), NameCharCountBytes);
    file.write(srcData.getName().c_str(), temp8bit);

    // Description
    temp8bit = srcData.getDescription().size();
    file.write((char*)(&temp8bit), DescCharCountBytes);
    file.write(srcData.getDescription().c_str(), temp8bit);

    // Move Speed
    temp8bit = srcData.getMoveSpeed();
    file.write((char*)(&temp8bit), MoveSpeedBytes);

    // Max Size
    temp8bit = srcData.getMaxSize();
    file.write((char*)(&temp8bit), MaxSizeBytes);

    // Commands
    temp8bit = commandIDs.size();
    file.write((char*)(&temp8bit), NumCommandsBytes);
    {
        uint8_t commandStrLen;
        commandIter = commandIDs.begin();
        for (uint8_t c = 0; c < temp8bit; c++, commandIter++)
        {
            commandStrLen = commandIter->size();
            file.write((char*)(&commandStrLen), IDCharCountBytes);
            file.write(commandIter->c_str(), commandStrLen);
        }
    }

    // Icon filepath.
    temp8bit = srcData.getIconFilepath().size();
    file.write((char*)(&temp8bit), IconFilepathCharCountBytes);
    file.write(srcData.getIconFilepath().c_str(), temp8bit);

    // Color
    {
        const sf::Color& color = srcData.getColor();
        uint8_t colorArray[ColorBytes] = { color.r, color.g, color.b };
        file.write((char*)colorArray, ColorBytes);
    }

    return true;
}

//==================================================================================================================================================