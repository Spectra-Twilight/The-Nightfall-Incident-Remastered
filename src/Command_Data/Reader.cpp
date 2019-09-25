#include <Spybot/Command_Data/Reader.hpp>

using namespace std;
using namespace Spybot;

//=============================================================================================================================================================

bool Command::Data::Reader::get(string& destID, Command& destData)
{
    if (!has())
        return false;
    
    uint16_t dataElementSize;
    uint8_t tempU8bit;
    int8_t tempS8bit;
    char tempStr[MaxStringSize];

    // Command Data format specified in Spybot/Command_Data/Interface.hpp

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Number of bytes for this data element.
    file.read((char*)(&dataElementSize), DataElementSizeBytes);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // ID
    getline(file, destID, '\0');

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Name
    file.getline(tempStr, MaxStringSize, '\0');
    destData.setName(tempStr);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Description
    file.getline(tempStr, MaxStringSize, '\0');
    destData.setDescription(tempStr);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Effect
    file.read((char*)(&tempU8bit), EffectBytes);
    switch (tempU8bit)
    {   //------------------------------------------------------------------------
        case 0: destData.setEffect(Effect::ModifySize);
        break;
        //------------------------------------------------------------------------
        case 1: destData.setEffect(Effect::ModifyMaxSize);
        break;
        //------------------------------------------------------------------------
        case 2: destData.setEffect(Effect::ModifySpeed);
        break;
        //------------------------------------------------------------------------
        case 3: destData.setEffect(Effect::ModifySector);
        break;
    }   //------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Strength
    file.read((char*)(&tempS8bit), StrengthBytes);
    destData.setStrength(tempS8bit);

    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    // Range
    file.read((char*)(&tempU8bit), RangeBytes);
    destData.setRange(tempU8bit);

    // Reset to beginning of element.
    file.seekg(-dataElementSize, ios_base::cur);
    return true;
}

//=============================================================================================================================================================