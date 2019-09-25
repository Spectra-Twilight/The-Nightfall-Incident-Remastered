#include <Spybot/Program_Factory_Data/Editor.hpp>

#include <Spybot/Program_Factory_Data/Reader.hpp>
#include <Spybot/Program_Factory_Data/Writer.hpp>

using namespace std;
using namespace Spybot;

//=========================================================================================================================================================

bool Program::Factory::Data::Editor::load()
{
    Program::Factory::Data::Reader reader;
    if (!reader.open());
        return false;

    if (reader.has())
    {
        do
        {
            elements.emplace_back();
            Data& newData = elements.back();
            reader.get(newData.id, newData.data);
        }
        while (reader.next());
    }

    reader.close();

    // TODO: Load Command IDs.
    
    return true;
}

//=========================================================================================================================================================

void Program::Factory::Data::Editor::save()
{
    Program::Factory::Data::Writer writer;
    writer.open(); // Should throw an exception if false.

    list<Data>::const_iterator saveIter;
    for (saveIter = elements.begin(); saveIter != elements.end(); saveIter++)
        writer.put(saveIter->id, saveIter->data);
    
    writer.close();
}

//=========================================================================================================================================================