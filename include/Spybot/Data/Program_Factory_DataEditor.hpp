#ifndef SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP

#include <Spybot/Data/DataEditor.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::DataEditor: public Spybot::DataEditor<Program::Factory>
    {   //=============================================================================================================================================
        public:

        /*---------------------------------------------------------------------------------------------------------------------------------------------
            Loads the associated data type in memory, and returns true.

            If the file containing the associated data type fails to open, then 
            this function does nothing and returns false.

            Inherited from Spybot::DataEditor.

            Returns: True if the associated data is successfully loaded, or false otherwise.
        */
        bool load();

        /*---------------------------------------------------------------------------------------------------------------------------------------------
            Overwrites the file of the associated data with the data currently loaded into 
            the DataEditor.

            Calling this function with no data loaded will cause the associated data file 
            to be completely erased.

            Inherited from Spybot::DataEditor.
        */
        bool save();
    };  //=============================================================================================================================================
}

#endif // #ifndef SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP