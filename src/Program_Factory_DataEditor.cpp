#include <Spybot/Data/Program_Factory_DataEditor.hpp>

#include <Spybot/Data/Program_Factory_DataReader.hpp>
#include <Spybot/Data/Program_Factory_DataWriter.hpp>

using namespace std;
using namespace Spybot;

//========================================================================================================================================================

bool Program::Factory::DataEditor::load()
{
    Program::Factory::DataReader reader;
    if (!reader.open())
        return false;

    if (reader.has())
    {
        do
        {
            elements.push_back(Data());
            reader.get(elements.back().id, elements.back().data);
        }
        while (reader.next());

        elemIter = elements.begin();
    }
    
    reader.close();
    return true;
}

//========================================================================================================================================================

bool Program::Factory::DataEditor::save()
{
    Program::Factory::DataWriter writer;
    if (!writer.open())
        return false;
    
    list<Data>::iterator saveIter;
    for (saveIter = elements.begin(); saveIter != elements.end(); saveIter++)
        writer.put(saveIter->id, saveIter->data);
    
    writer.close();
    return true;
}

//========================================================================================================================================================