#ifndef SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP

#include <string>

#include <Spybot/GameData/Reader.hpp>
#include <Spybot/Program_Factory_Data/Interface.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::Data::Reader: public Program::Factory::Data::Interface, public GameData::Reader<Program::Factory>
    {   //================================================================================================================================================
        public:

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Reader(): GameData::Interface(ProgramData) {}

        /*------------------------------------------------------------------------------------------------------------------------------------------------
            Overwrites the fields of the provided argument string and Program::Factory with 
            the data currently pointed to by this Reader at the time of the call to this function, 
            then returns true. The data pointer of this Reader resets to the position it began 
            a call to this function at before returning.

            If the currently associated data has not yet been opened, or no data exists to read, then 
            then arguments will not be modified and the function returns false.

            Parameters:
            *   destID: Reference to the string in which to store the ID of the loaded data.
            *   destData: Reference to the Program::Factory in which to store the attributes of the loaded data.
            
            Returns: True if the data was loaded into the arguments successfully, or false otherwise.
        */
        bool get(std::string& destID, Program::Factory& destData);

    };  //================================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP