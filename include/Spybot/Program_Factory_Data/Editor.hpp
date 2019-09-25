#ifndef SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP

#include <list>
#include <string>

#include <Spybot/GameData/Editor.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::Data::Editor: public GameData::Editor<Program::Factory>
    {   //=====================================================================================================================================================

        private:
        std::list<std::string> commandIDs; // Used for assigning only valid commands to programs.

        //=====================================================================================================================================================

        public:
        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Returns a list of command IDs, for use in assigning commands to programs.

            Returns: A list of strings representative of command IDs.
        */
        inline const std::list<std::string>& getCommandIDs() { return commandIDs; }

        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Loads the associated data type in memory, and returns true.

            If the file containing the associated data type fails to open, then 
            this function does nothing and returns false.

            Inherited from Spybot::GameData::Editor.

            Returns: True if the associated data is successfully loaded, or false otherwise.
        */
        bool load();
        
        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Overwrites the file of the associated data with the data currently loaded into 
            the this object, then returns true.

            If the function fails to open data associated data for writing for any reason, 
            the function does nothing and returns false.

            Calling this function with no data loaded will cause the associated data file's 
            data to be entirely erased.

            Inherited from Spybot::GameData::Editor.
        */
        void save();
        
    };  //=====================================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_EDITOR_HPP