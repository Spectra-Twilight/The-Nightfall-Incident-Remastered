#ifndef SPYBOT_GAME_DATA_INTERFACE_HPP
#define SPYBOT_GAME_DATA_INTERFACE_HPP

#include <cstdint>
#include <string>

namespace Spybot
{
    namespace GameData
    {
        class Interface
        {   //=================================================================================================================================================
            protected:

            constexpr static uint8_t NumElementsBytes = 4; // Number of bytes used to count the number to data elements within a file.
            constexpr static uint8_t DataElementSizeBytes = 2; // Number of bytes used to track the total size (in bytes) of a data element.
            constexpr static uint16_t MaxStringSize = 1024; // Maximum number of characters allowed for strings.
            const std::string filepath;

            inline Interface(const std::string& initFilepath): filepath(initFilepath) {}

            //=================================================================================================================================================
            public:
            
            /*-------------------------------------------------------------------------------------------------------------------------------------------------
                Closes the associated GameData.
            */
            virtual void close() = 0;

            /*-------------------------------------------------------------------------------------------------------------------------------------------------
                Opens the associated GameData, begins pointing to the first data element, and returns true. 
                If the associated GameData cannot be accessed for any reason, the function does nothing 
                then returns false.

                Returns: True if the associated GameData was opened, or false otherwise.
            */
            virtual bool open() = 0;

        };  //=================================================================================================================================================
    }
}

#endif // SPYBOT_GAME_DATA_INTERFACE_HPP