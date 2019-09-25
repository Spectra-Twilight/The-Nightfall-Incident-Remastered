#ifndef SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP
#define SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP

#include <Spybot/Data/DataInterface.hpp>
#include <Spybot/Program_Factory.hpp>

namespace Spybot
{
    class Program::Factory::DataInterface: public virtual Spybot::DataInterface
    {
        protected:
        constexpr static uint8_t NameCharCountBytes = 1; // Number of bytes used to count the characters in a stored name.
        constexpr static uint8_t DescCharCountBytes = 1; // Number of bytes used to count the characters in a stored description.
        constexpr static uint8_t MoveSpeedBytes = 1; // Number of bytes used to store movement speed.
        constexpr static uint8_t MaxSizeBytes = 1; // Number of bytes used to store maximum program size.
        constexpr static uint8_t NumCommandsBytes = 1; // Number of bytes used to count the number of commands stored.
        constexpr static uint8_t IconFilepathCharCountBytes = 1; // Number of bytes used to count the characters in a stored icon filepath.
        constexpr static uint8_t ColorBytes = 3; // Number of bytes used to store program color.

        /*  Program::Factory data is formatted as follows:

            *  Data Element Size (Number of bytes defined by DataElementSizeBytes defined in Spybot::DataInterface.hpp)
            *  ID Character Count (Number of bytes defined by IDCharCountBytes defined in Spybot::DataInterface.hpp)
            *  ID
            *  Name Character Count
            *  Name 
            *  Description Character Count
            *  Description
            *  Move Speed
            *  Max Size
            *  Number of Commands
            for all commands:
            {
            *  *    Command ID Character Count (Number of bytes defined by IDCharCountBytes defined in Spybot::DataInterface.hpp)
            *  *    Command ID
            }
            *   Icon Filepath Character Count
            *   Icon Filepath
            *   Color (Stored as an RGB value).
        */

        inline const static std::string ProgramData = "data/programs.dat";
    };
}


#endif // SPYBOT_PROGRAM_FACTORY_DATA_INTERFACE_HPP