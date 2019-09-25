#ifndef SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP

#include <string>

#include <Spybot/Data/DataReader.hpp>
#include <Spybot/Data/Program_Factory_DataInterface.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::DataReader: public Program::Factory::DataInterface, public Spybot::DataReader<Program::Factory>
    {   //==========================================================================================================================================
        public:

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline DataReader(): Spybot::DataInterface(ProgramData) {}

        /*--------------------------------------------------------------------------------------------------------------------------------------------
            Populates the argument string with the current element's ID, and the appropriate 
            argument data variable's attributes with the current element's attributes, then 
            returns true.

            If the file is not open or not pointing to any data element (such as when the data 
            file is empty) at the time of the call to this function, the function returns false 
            and neither argument variable is modified.

            Inherited from Spybot::DataReader.

            Parameters:
            *   idDest: Destination for the ID of the current data.
            *   dataDest: Destination for the current data.
            
            Returns: True if the current data was successfully written into the arguments, or false otherwise.
        */
        bool get(std::string& destID, Factory& destData);

    };  //==========================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_READER_HPP