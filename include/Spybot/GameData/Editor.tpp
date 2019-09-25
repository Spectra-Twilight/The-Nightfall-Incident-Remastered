// Template implementation source. Should NOT have an include statement to its header.

//===========================================================================================================================================================

void Spybot::GameData::Editor<T>::add(const std::string& srcID, const T& srcData)
{
    elements.push_back(Data());
    elements.back().id = srcID;
    elements.back().data = srcData;
    elemIter = elements.end();
    elemIter--;
}

//===========================================================================================================================================================

inline int Spybot::GameData::Editor<T>::count() const 
{ 
    return elements.size();
}

//===========================================================================================================================================================

bool Spybot::GameData::Editor<T>::find(const std::string& ID)
{
    typename std::list<Data>::iterator original = elemIter;
    
    for (elemIter = elements.begin(); elemIter != elements.end(); elemIter++)
    {
        if (elemIter->id == ID)
            return true;
    }

    elemIter = original;
    return false;
}

//===========================================================================================================================================================

bool Spybot::GameData::Editor<T>::get(std::string** destID, T** destData)
{
    if (elements.size() == 0)
        return false;
    
    *destID = &(elemIter->id);
    *destData = &(elemIter->data);
    return true;
}

//===========================================================================================================================================================

void Spybot::GameData::Editor<T>::getIDList(std::list<std::string>& destList)
{
    destList.clear();
    typename std::list<Data>::const_iterator tempIter;
    for (tempIter = elements.begin(); tempIter != elements.end(); tempIter++)
        destList.push_back(tempIter->id);
}

//===========================================================================================================================================================

void Spybot::GameData::Editor<T>::next()
{
    elemIter++;

    if (elemIter == elements.end())
        elemIter = elements.begin();
}

//===========================================================================================================================================================

void Spybot::GameData::Editor<T>::prev()
{
    if (elemIter == elements.begin())
        elemIter = elements.end();

    elemIter--;
}

//===========================================================================================================================================================

bool Spybot::GameData::Editor<T>::remove()
{
    if (elements.size() == 0)
        return false;
    
    elemIter = elements.erase(elemIter);
    if (elemIter == elements.end())
        elemIter = elements.begin();

    return true;
}

//===========================================================================================================================================================

inline void Spybot::GameData::Editor<T>::unload()
{
    elements.clear();
}

//===========================================================================================================================================================