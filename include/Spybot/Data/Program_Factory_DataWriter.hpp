#ifndef SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP

#include <string>

#include <Spybot/Data/DataWriter.hpp>
#include <Spybot/Program_Factory.hpp>
#include <Spybot/Data/Program_Factory_DataInterface.hpp>

namespace Spybot
{
    class Program::Factory::DataWriter: public Program::Factory::DataInterface, public Spybot::DataWriter<Program::Factory>
    {   //=============================================================================================================================================
        public:

        /*---------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        DataWriter(): Spybot::DataInterface(ProgramData) {}

        /*------------------------------------------------------------------------------------------------------------------------------------
            Writes srcData to the stream under the ID provided by srcID, then returns true.

            If the stream is not currently open at the time of the call to this function, then 
            this function returns false and does nothing else.

            Inherited from Spybot::DataWriter.

            Parameters:
            *   srcID: The ID under which to identify the data being stored.
            *   srcData: The data to store.
            
            Returns: True if the data was written to the stream, or false otherwise.
        */
        bool put(const std::string& srcID, const Factory& srcData);

    };  //=============================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_WRITER_HPP