#ifndef SPYBOT_COMMAND_DATA_READER_HPP
#define SPYBOT_COMMAND_DATA_READER_HPP

#include <Spybot/Command.hpp>

#include <string>

#include <Spybot/Command_Data/Interface.hpp>
#include <Spybot/GameData/Reader.hpp>

namespace Spybot
{
    class Command::Data::Reader: public Command::Data::Interface, public GameData::Reader<Command>
    {   //=============================================================================================================================================
        public:

        /*---------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Reader(): GameData::Interface(CommandData) {}

        /*---------------------------------------------------------------------------------------------------------------------------------------------
            Overwrites the provided argument string and the attributes of the provided Command object
            with the id and Command attribute data that this object is currently pointing to at the 
            time of the call to this function, then returns true.

            If this object is not currently pointing to any data (such as if this object's data stream is 
            not open or if the stream is empty), then this function returns false and the arguments 
            are not modified.

            After a call to this function, regardless of the outcome, this object will continue to point 
            at the same data element (as in: a successful read will not advance the data pointer).

            Parameters:
            *   destID: A reference to a string in which the ID of the data currently pointed to will be stored.
            *   destData: A reference to a Command object in which the attributes of the data currently pointed to will be stored.
        */
        bool get(std::string& destID, Command& destData);

    };  //=============================================================================================================================================
}

#endif // SPYBOT_COMMAND_DATA_READER_HPP