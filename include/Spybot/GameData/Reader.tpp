// Template implementation source. Should NOT have an include statement to its header.

#include <Log.hpp>

//====================================================================================================================================================================

template <typename T>
inline Spybot::GameData::Reader<T>::Reader(): numDataElements(0), currDataElement(1) {}

//====================================================================================================================================================================

template <typename T>
inline void Spybot::GameData::Reader<T>::close()
{
    if (file.is_open())
    {
        file.close();
        numDataElements = 0;
        currDataElement = 1;
    }
}

//====================================================================================================================================================================

template <typename T>
inline uint32_t Spybot::GameData::Reader<T>::count() const
{
    return numDataElements;
}

//====================================================================================================================================================================

template <typename T>
bool Spybot::GameData::Reader<T>::find(const std::string& requestedID)
{
    if (numDataElements == 0)
        return false;

    std::streampos originalPos = file.tellg();
    uint32_t originalElement = currDataElement;
    std::string currID;

    file.seekg(NumElementsBytes, std::ios_base::beg); // Start of first element's byte count.
    currDataElement = 1;

    if (has())
    {
        do
        {
            getID(currID);
            if (requestedID == currID)
                return true;
        } 
        while (next());
    }
    else
        LOG(Log::Level::ERROR) << filepath << " is empty, but reports having " << (int)numDataElements << " elements.";
    

    file.seekg(originalPos, std::ios_base::beg);
    currDataElement = originalElement;
    return false;
}

//====================================================================================================================================================================

template <typename T>
bool Spybot::GameData::Reader<T>::getID(std::string& dest)
{
    if (!has())
        return false;

    file.seekg(DataElementSizeBytes, std::ios_base::cur); // Skip over data element size counter.

    // Save ID in file to ID variable.
    getline(file, dest, '\0');

    file.seekg(-(DataElementSizeBytes + dest.size() + 1), std::ios_base::cur); // Return to original position.
    return true;
}

//====================================================================================================================================================================

template <typename T>
inline bool Spybot::GameData::Reader<T>::has()
{
    return (currDataElement <= numDataElements);
}

//====================================================================================================================================================================

template <typename T>
bool Spybot::GameData::Reader<T>::next()
{
    if (currDataElement >= numDataElements)
        return false;

    std::streampos original = file.tellg();
    uint16_t dataElementSize;
    file.read((char*)(&dataElementSize), DataElementSizeBytes);
    file.seekg(dataElementSize - DataElementSizeBytes, std::ios_base::cur);

    if (file.peek() == EOF)
    {
        LOG(Log::Level::ERROR) << filepath << " ended unexpectedly (" << (int)currDataElement << "/" << (int)numDataElements << " data elements found).";
        file.seekg(original, std::ios_base::beg);
        return false;
    }

    currDataElement++;
    return true;
}

//====================================================================================================================================================================

template <typename T>
bool Spybot::GameData::Reader<T>::open()
{
    if (file.is_open())
        file.close();
    
    file.open(filepath, std::ios_base::binary);
    if (!file.is_open())
        return false;
    
    file.read((char*)(&numDataElements), NumElementsBytes);
    return true;
}

//====================================================================================================================================================================