#ifndef SPYBOT_COMMAND_DATA_INTERFACE_HPP
#define SPYBOT_COMMAND_DATA_INTERFACE_HPP

#include <cstdint>
#include <string>

#include <Spybot/Command.hpp>
#include <Spybot/GameData/Interface.hpp>

namespace Spybot
{
    class Command::Data::Interface: public virtual GameData::Interface
    {   //=====================================================================================================================================================
        protected:

        constexpr static uint8_t EffectBytes = 1; // The number of bytes used to store effect type.
        constexpr static uint8_t StrengthBytes = 1; // The number of bytes used to store strength of an effect.
        constexpr static uint8_t RangeBytes = 1; // The number of bytes used to store range of an effect.

        inline const static std::string CommandData = "data/commands.dat";

        /*
            Command Data elements are formatted on file as follows:
            *   Data Element Size (Number of bytes defined by GameData::Interface::DataElementSizeBytes)
            *   ID (null-terminated)
            *   Name (null-terminated)
            *   Description (null-terminated)
            *   Effect (Number of bytes determined by EffectBytes)
            * *     0: Damage
            * *     1: Growth
            * *     2: MaxSizeUp
            * *     3: MaxSpeedUp
            * *     4: MaxSpeedDown
            *   Strength (Number of bytes determined by StrengthBytes)
            *   Range (Number of bytes determined by RangeBytes)
        */

        /*-----------------------------------------------------------------------------------------------------------------------------------------------------
            Default constructor.
        */
        inline Interface() {}

    };  //=====================================================================================================================================================
}

#endif // SPYBOT_COMMAND_DATA_INTERFACE_HPP