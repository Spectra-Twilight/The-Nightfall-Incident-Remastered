#ifndef SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP

#include <cstdint>
#include <string>

#include <Spybot/GameData/Interface.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::Data::Interface: public virtual Spybot::GameData::Interface
    {   //====================================================================================================================================================
        protected:

        constexpr static uint8_t MoveSpeedBytes = 1; // Number of bytes used to store movement speed.
        constexpr static uint8_t MaxSizeBytes = 1; // Number of bytes used to store maximum program size.
        constexpr static uint8_t NumCommandsBytes = 1; // Number of bytes used to count the number of commands stored.
        constexpr static uint8_t ColorBytes = 3; // Number of bytes used to store program color.

        /*  Program::Factory data is formatted as follows:

            *  Data Element Size (Number of bytes defined by DataElementSizeBytes defined in Spybot::DataInterface.hpp)
            *  ID (null-terminated)
            *  Name (null-terminated)
            *  Description (null-terminated)
            *  Move Speed
            *  Max Size
            *  Number of Commands
            *  Command ID for each command (each is null-terminated)
            *  Graphic ID
            *  Color (Stored as an RGB value).
        */

        inline const static std::string ProgramData = "data/programs.dat";

        /*----------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Interface() {}

    };  //====================================================================================================================================================
}

#endif // SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP