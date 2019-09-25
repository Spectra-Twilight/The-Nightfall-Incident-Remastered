#ifndef SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP

#include <string>

#include <Spybot/GameData/Writer.hpp>
#include <Spybot/Program_Factory_Data/Interface.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::Data::Writer: public Program::Factory::Data::Interface, public GameData::Writer<Program::Factory>
    {   //===================================================================================================================================================
        public:

        /*---------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Writer(): GameData::Interface(ProgramData) {}

        /*---------------------------------------------------------------------------------------------------------------------------------------------------
            Writes the ID and attribute data of the arguments into program data, 
            and returns true. After a call to this function, the Writer's data pointer is 
            automatically advanced just past the end of the most recently written data element.

            If the program data is not currently open at the time of the call to this function, 
            then this function does nothing and returns false.

            Parameters:
            *   srcID: Reference to a string containing the ID of the element being written.
            *   srcData: Reference to a Program::Factory containing attribute data to be written as a new element.
            
            Returns: True if the write was successful, or false otherwise.
        */
        bool put(const std::string& srcID, const Program::Factory& srcData);

    };  //===================================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP